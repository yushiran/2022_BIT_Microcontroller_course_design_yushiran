#!/usr/bin/env python
# -*- coding: utf-8 -*-

#warning: this py can only compile under Python3.x

import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import font
from tkinter import filedialog
from tkinter import messagebox
import threading, time, subprocess, types
import os, sys, struct, re
import time
import platform
import ctypes

re_files = "mv_download_.*\.exe"
re_cpu_type = 'CPU_VER=([0-9a-f]+)\((\w+) Rev:(\w+)\)'

__author__ = "Castle Cai"
__copyright__ = "Copyright 2018, The Downloader Project"

__license__ = "GPL"
__version__ = "1.1.0"
__maintainer__ = "Castle Cai"
__email__ = "castleodinland@gmail.com"
__status__ = "Internal Test Beta"

cpu_type_list = [
['D10', '0x0c', 'O26', 'mv_download_o26_.*\.exe'],
['D10', '0x11', 'B1', 'mv_download_b1_.*\.exe'],
['N968', '0x18', 'P20', 'mv_download_p20_.*\.exe'],
]


class Application(Frame):

    def printkey(self, event):
        print ('press key:' + event.char)

    def get_path(self):
        # determine if application is a script file or frozen exe
        if getattr(sys, 'frozen', False):
            application_path = os.path.dirname(sys.executable)
        elif __file__:
            application_path = os.path.dirname(__file__)

        return application_path

    def start_to_download(self):
        #self.dl_thread = thread.start_new_thread(self.run_burn, ())
        self.dl_thread = threading.Thread(target=self.run_burn)
        self.dl_thread.start()
        return

    def need_verify(self):
        #print('verify=%d'%(self.verify.get()))
        if self.verify.get() == 1:
            return '--verify'
        else:
            return ''

    def need_erase_all(self):
        #print('verify=%d'%(self.verify.get()))
        if self.eraseall.get() == 1:
            return '--erase-all'
        else:
            return ''

    def disable_buttons(self):
        self.brun["state"] = 'disable'
        self.bstop["state"] = 'disable'
        self.bcheckcpu["state"] = 'disable'

    def enable_buttons(self):
        self.brun["state"] = 'normal'
        self.bstop["state"] = 'normal'
        self.bcheckcpu["state"] = 'normal'

    def refresh_noraml(self):
        self.ttext.see(END)
        os.chdir(self.get_path())
        self.enable_buttons()


    def filter_dl_exe(self, core_type, core_rev):
        exe_file_count = 0
        for cpu_item in cpu_type_list:
            if core_type == cpu_item[0] and core_rev == cpu_item[1]:
                self.dl_list = []
                print('main path: %s'%(self.get_path()))
                for dirpath, dirnames, filenames in os.walk(self.get_path()):
                    #print('current path: %s'%(dirpath))
                    #if self.get_path() == dirpath:
                    if self.get_path() + '\\' + 'flash_downloader' == dirpath:
                        for name in filenames:
                            #print('-----%s'%(name))
                            if re.compile(cpu_item[3], re.I).match(name):
                                self.dl_list.append(name)
                        break
                self.listCom['values'] = self.dl_list
                exe_file_count = len(self.dl_list)
                if len(self.dl_list) > 0:
                    self.listCom.set(self.dl_list[len(self.dl_list)-1])
                else:
                    self.listCom.set('')
                self.ttext.insert(END, "Current chip type: %s\n"%(cpu_item[2]))
                self.ttext.see(END)
                break;
        return exe_file_count

    def mva2bin(self, fullpath):
        try:
            with open(fullpath, "rb") as datafile:
                (mvo,dummy,package_count) = struct.unpack('<3sBB',datafile.read(5))
                #bb = struct.unpack('3sBB8s',datafile.read(13))
                #print(mov)
                #print(package_count)
                if mvo != b'MVO':
                    return ''

                for i in range(0,package_count):
                    #print(i)
                    (ptype,length) = struct.unpack('<BL',datafile.read(5))
                    print("type=%d, length=%d"%(ptype, length))
                    if ptype == 2:
                        datafile.read(4) #offset

                        (filepath,tempfilename) = os.path.split(fullpath);
                        (shotname,extension) = os.path.splitext(tempfilename);
                        #binfilename_full = os.path.join(filepath, shotname)+'.bin'
                        binfilename_full = filepath + '/'+ shotname +'.bin'

                        with open(binfilename_full, "wb") as outbin:
                            outbin.write(datafile.read(length-4))
                        return binfilename_full
                    else:
                        datafile.read(length)
            return ''
        except Exception as e:
            print(Exception)
            print(e)
            return ''


    def run_burn(self):

        if not self.HexFile:
            self.ttext.insert(END, "No Bin file selected...\n")
            self.ttext.see(END)
            return

        self.disable_buttons()

        new_env = os.environ.copy()
        sys_env = os.environ
        #print sys_env['PATH']
        #new_env['PATH'] = sys_env['PATH'] + ';' + os.getcwd() + '\\dll' + ';C:\Windows\SysWOW64;C:\WINDOWS\system32'
        new_env['PATH'] = self.get_path() + '\\dll' + ';C:\Windows\SysWOW64;C:\WINDOWS\system32'
        os.system('tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe')
        os.system('tasklist|find /i "nds32le-elf-gdb.exe" && taskkill /f /t /im nds32le-elf-gdb.exe')

        iceman_run = 'ICEman.exe -b 9900 -t 9901 -p 9902 -A -N reset-hold-script.tpl -H'
        si = subprocess.STARTUPINFO()
        si.dwFlags = subprocess.CREATE_NEW_CONSOLE | subprocess.STARTF_USESHOWWINDOW
        si.wShowWindow = subprocess.SW_HIDE
        try:
            os.chdir(self.get_path() + '\ice')
            self.current_process = subprocess.Popen(iceman_run,
                               shell=False,
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT,
                               env=new_env,
                               #startupinfo=si)
                               )
            #errcode = self.current_process.wait()
        except Exception as e:
            self.ttext.insert(END, "Exception: %r\n" % (e) )
            self.refresh_noraml()
            return
        tstr = self.current_process.stdout.readline()
        while tstr:
            self.ttext.insert(END, tstr)
            self.ttext.see(END)
            #print '--' + tstr
            if "ICEman is ready to use.".encode('utf-8') in tstr:
                break
            tstr = self.current_process.stdout.readline()
        if not tstr:
            self.ttext.insert(END, "ICEman connect failed, return!\n")
            self.refresh_noraml()
            return

        dl_exe_fullname = self.get_path() + '\\' + 'flash_downloader' + '\\' + self.listCom.get()
        self.ttext.insert(END, dl_exe_fullname + '\n')
        self.ttext.see(END)
        #print 'END1'

        timeStamp = time.time()
        iceman_run = '%s --image %s --addr %s %s %s --port 9900'%(dl_exe_fullname, self.HexFile, self.addr.get(), self.need_verify(), self.need_erase_all())

        try:
            os.chdir(self.get_path())
            self.current_process2 = subprocess.Popen(iceman_run,
                               shell=False,
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT,
                               env=new_env,
                               #startupinfo=si)
                               )
            #errcode = self.current_process.wait()
        except Exception as e:
            #self.returnAndReloaderWidgets('Erase failed!', 'red', 'active')
            self.ttext.insert(END, "Exception: %r\n" % (e) )
            self.refresh_noraml()
            return

        tstr = self.current_process2.stdout.readline()
        while tstr:
            self.ttext.insert(END, tstr)
            self.ttext.see(END)
            if "Flash burn success.".encode('utf-8') in tstr:
                self.ttext.insert(END, 'Spend time: %.2f seconds'%(time.time()-timeStamp))
            elif "Flash burn done.".encode('utf-8') in tstr:
                self.ttext.insert(END, 'Spend time: %.2f seconds'%(time.time()-timeStamp))
            tstr = self.current_process2.stdout.readline()

        self.refresh_noraml()
        return

    def reset_and_run(self):
        self.disable_buttons()
        new_env = os.environ.copy()
        sys_env = os.environ
        #print sys_env['PATH']
        #new_env['PATH'] = sys_env['PATH'] + ';' + os.getcwd() + '\\dll' + ';C:\Windows\SysWOW64;C:\WINDOWS\system32'
        new_env['PATH'] = self.get_path() + '\\dll' + ';C:\Windows\SysWOW64;C:\WINDOWS\system32'
        os.system('tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe')
        os.system('tasklist|find /i "nds32le-elf-gdb.exe" && taskkill /f /t /im nds32le-elf-gdb.exe')

        iceman_run = 'ICEman.exe -b 9900 -t 9901 -p 9902 -A -N reset-hold-script.tpl -H'
        try:
            os.chdir(self.get_path() + '\ice')
            self.current_process3 = subprocess.Popen(iceman_run,
                               shell=False,
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT,
                               env=new_env)
            #errcode = self.current_process.wait()
        except Exception as e:
            #self.returnAndReloaderWidgets('Erase failed!', 'red', 'active')
            self.ttext.insert(END, "Exception: %r\n" % (e) )
            self.refresh_noraml()
            return
        tstr = self.current_process3.stdout.readline()
        while tstr:
            self.ttext.insert(END, tstr)
            self.ttext.see(END)
            #print '--' + tstr
            if "ICEman is ready to use.".encode('utf-8') in tstr:
                break
            tstr = self.current_process3.stdout.readline()

        if not tstr:
            self.ttext.insert(END, "ICEman connect failed, return!\n")
            self.refresh_noraml()
            return

        self.ttext.see(END)

        print ('ENDICEM')
        #return

        iceman_run = 'nds32le-elf-gdb.exe -x dbg_reset_and_run.txt'
        try:
            os.chdir(self.get_path() + '\\dbg\\bin')
            self.current_process4 = subprocess.Popen(iceman_run,
                               shell=False,
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT,
                               env=new_env)
            #errcode = self.current_process4.wait()
        except Exception as e:
            #self.returnAndReloaderWidgets('Erase failed!', 'red', 'active')
            self.ttext.insert(END, "Exception: %r\n" % (e) )
            self.refresh_noraml()
            return
        tstr = self.current_process4.stdout.readline()
        while tstr:
            self.ttext.insert(END, tstr)
            self.ttext.see(END)
            #print '--' + tstr
            tstr = self.current_process4.stdout.readline()
        self.ttext.insert(END, "\n---Reset successfully---\n")
        self.refresh_noraml()
        return

    def check_cpu_run(self):

        if not self.HexFile:
            self.ttext.insert(END, "No Bin file selected...\n")
            self.ttext.see(END)
            return

        self.disable_buttons()
        new_env = os.environ.copy()
        sys_env = os.environ
        #print sys_env['PATH']
        #new_env['PATH'] = sys_env['PATH'] + ';' + os.getcwd() + '\\dll' + ';C:\Windows\SysWOW64;C:\WINDOWS\system32'
        new_env['PATH'] = self.get_path() + '\\dll' + ';C:\Windows\SysWOW64;C:\WINDOWS\system32'
        os.system('tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe')
        os.system('tasklist|find /i "nds32le-elf-gdb.exe" && taskkill /f /t /im nds32le-elf-gdb.exe')

        iceman_run_x = 'ICEman.exe -x'

        ##################################################################################################
        self.ttext.insert(END, 'checking cpu type, please wait...\n')
        try:
            os.chdir(self.get_path() + '\ice')
            self.current_process5 = subprocess.Popen(iceman_run_x,
                               shell=False,
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.STDOUT,
                               env=new_env)
            #errcode = self.current_process.wait()
        except Exception as e:
            #self.returnAndReloaderWidgets('Erase failed!', 'red', 'active')
            self.ttext.insert(END, "Exception: %r\n" % (e) )
            self.refresh_noraml()
            return
        tstr = self.current_process5.stdout.readline()
        while tstr:
            #self.ttext.insert(END, tstr)
            #self.ttext.see(END)
            #self.ttext.insert(END, '.\n')
            print(tstr.decode('utf-8'))
            cpu_type_ree = re.match(re_cpu_type, tstr.decode('utf-8'))
            if cpu_type_ree:
                self.ttext.insert(END, 'cpu type=%s, revision=%s\n'%(cpu_type_ree.group(2), cpu_type_ree.group(3)))
                exe_count = self.filter_dl_exe(cpu_type_ree.group(2), cpu_type_ree.group(3))
                self.ttext.insert(END, 'found %d downloader exe\n'%(exe_count))
                if exe_count == 0:
                    self.ttext.insert(END, 'no downloader found...\n')
                    self.stopall()
                    self.enable_buttons()
                    return
            tstr = self.current_process5.stdout.readline()

        self.ttext.insert(END, 'check cpu finished.\n')
        self.ttext.see(END)

        #real download
        self.run_burn()
        self.enable_buttons()
        return


    def returnAndReloaderWidgets(self, label_text, label_bg, brun_state):
        self.brun["state"] = brun_state
        if(brun_state == 'active'):
            self.brun['fg'] = 'blue'

    def connect_to_dbg(self):
        self.rh_thread = threading.Thread(target=self.reset_and_run)
        self.rh_thread.start()
        #root.quit()

    def checkcpu(self):
        self.rh_thread = threading.Thread(target=self.check_cpu_run)
        self.rh_thread.start()

    def selectHexFile(self):
        #self.HexFile = ''
        #print('show bin dir:' + self.get_path() + '\\bin')
        #self.HexFile = filedialog.askopenfilename(initialdir = self.get_path()+ '\\bin', filetypes=[("BIN Files", ".bin"),("MVA Files", ".mva")])
        self.HexFile = filedialog.askopenfilename(initialdir = self.get_path()+ '\\bin', filetypes=[("Code Files", "*.bin;*.mva")])

        if(self.HexFile):
            (filepath,tempfilename) = os.path.split(self.HexFile);
            (shotname,extension) = os.path.splitext(tempfilename);
            if extension.lower() == '.mva':
                print(os.path.join(filepath, shotname))
                self.HexFile = self.mva2bin(self.HexFile)
                if(self.HexFile):
                    self.ttext.insert(END, 'BIN file From .mva: ' + self.HexFile + '\n')
                    self.llabel['text'] = os.path.basename(self.HexFile)
                else:
                    messagebox.showerror("Error", "Not a valid MVA file!!!")
                    self.ttext.insert(END, 'No BIN file selected.' + '\n')
                    self.llabel['text'] = "File not select"
            else:
                self.ttext.insert(END, 'BIN file: ' + self.HexFile + '\n')
                self.llabel['text'] = os.path.basename(self.HexFile)
        else:
            self.ttext.insert(END, 'No BIN file selected.' + '\n')
            self.llabel['text'] = "File not select"

    def copy(self, editor, event=None):
        editor.event_generate("<<Copy>>")

    def clear(self, editor, event=None):
        self.ttext.delete(0.0, END)

    def rightKey(self, event, editor):
        ftLabel = font.Font(family = 'Verdana', size = 20)
        self.menubar.delete(0,END)
        self.menubar.add_command(label='clear',command=lambda:self.clear(editor), font = ftLabel)
        self.menubar.add('separator')
        self.menubar.add_command(label='copy',command=lambda:self.copy(editor), font = ftLabel)
        self.menubar.post(event.x_root,event.y_root)

    def stopall(self):
        self.terminate_all_process()
        #self.ttext.delete(0.0, END)
        self.refresh_noraml()
        self.ttext.insert(END, "\nStop OK!\n")

    def createWidgets(self, main_frame):
        ftLabel = font.Font(family = 'Verdana', size = 20, weight = font.BOLD)
        ftText = font.Font(family = 'Verdana', size = 10, weight = font.BOLD)
        ftButton = font.Font(family = 'Verdana', weight = font.BOLD)
        smallLabel = font.Font(family = 'Verdana', size = 8)

        #self.llabel = Label(main_frame, text="Ready", width=20, bg="turquoise", font = ftLabel)
        #self.llabel.grid(row=0, column=0, sticky=W+E) #columnspan=2

        self.menubar = Menu(main_frame,tearoff=False)

        self.frame1 = Frame(main_frame)
        self.frame1.grid(row=0, column=0, columnspan=2, sticky=W+E+N+S)

        self.addr = StringVar()
        self.addrtext = Entry(self.frame1, width=18, font = ftLabel, textvariable = self.addr)
        self.addrtext.grid(row=0, column=0, sticky=W+E+N+S)
        self.addr.set("0x00")
        self.addrtext.bind('<Key>', self.printkey)
        self.addrtext['background'] = '#cce8cc'

        self.bfile = Button(self.frame1, text='BIN File', width=12, font = ftButton, bg="#6495ED")
        self.bfile.grid(row=0, column=3, sticky=W+E+N+S)
        self.bfile["command"] = self.selectHexFile

        self.verify = IntVar()
        self.verify.set(0)
        self.checkbutton = Checkbutton(self.frame1, text='verify', variable = self.verify, font = ftButton)
        self.checkbutton.grid(row=0, column=1)

        self.eraseall = IntVar()
        self.eraseall.set(0)
        self.checkbutton_e = Checkbutton(self.frame1, text='eraseall', variable = self.eraseall, font = ftButton)
        self.checkbutton_e.grid(row=0, column=2)


        self.xfile = Button(self.frame1, text='STOP', width=10, font = ftButton, bg="Red")
        self.xfile.grid(row=0, column=4, sticky=W+E+N+S)
        self.xfile["command"] = self.stopall

        self.ttext = Text(main_frame, font = ftText, height=35)
        self.ttext.grid(row=1, column=0,columnspan=2, sticky=W+E)
        self.ttext['background'] = '#cce8cc'
        self.ttext.bind("<Button-3>", lambda x: self.rightKey(x, self.ttext))
        #self.ttext['state'] = 'normal'
        #self.ttext.bind("<KeyPress>", lambda e : "break")

        #self.pbar = ttk.Progressbar(main_frame)
        #self.pbar.grid(row=2, column=0, columnspan=2, sticky=W+E+N+S)

        self.scrollbar = Scrollbar(main_frame)
        self.scrollbar.grid(row=1, column=1, sticky=N+S+E)
        self.scrollbar.config(command=self.ttext.yview)
        self.ttext['yscrollcommand'] = self.scrollbar.set

        self.dl_list = []
        print('main path: %s'%(self.get_path()))
        for dirpath, dirnames, filenames in os.walk(self.get_path()):
            #print('current path: %s'%(dirpath))
            #if self.get_path() == dirpath:
            if self.get_path() + '\\' + 'flash_downloader' == dirpath:
                for name in filenames:
                    #print('-----%s'%(name))
                    if re.compile(re_files, re.I).match(name):
                        self.dl_list.append(name)
                break

        self.listCom = ttk.Combobox(main_frame,  width=15, font = ftButton, state='readonly')
        self.listCom.grid(row=2, column=0, sticky=W+E+N+S)
        self.listCom['values'] = self.dl_list
        self.listCom['state'] ='readonly'
        #self.listCom.bind('<<ComboboxSelected>>', lambda event: self._click_combo())
        if len(self.dl_list) > 0:
            self.listCom.set(self.dl_list[len(self.dl_list)-1])
        #self.listCom['background'] = '#cce8cc'

        self.llabel = Label(main_frame, text="File not select", width=20, bg="Cyan", font = smallLabel, anchor='w')
        self.llabel.grid(row=2, column=1, sticky=W+E, columnspan=2) #columnspan=2

        self.brun = Button(main_frame, text='DOWNLOAD', width=15, font = ftButton, bg="DeepSkyBlue")
        self.brun.grid(row=3, column=0, sticky=W+E+N+S)
        self.bstop = Button(main_frame, text='RESET AND RUN', width=15, font = ftButton, bg="DarkOrange")
        self.bstop.grid(row=4, column=0, sticky=W+E+N+S)

        self.bcheckcpu = Button(main_frame, text='Auto Check\n& Download BIN', width=20, font = ftButton, bg="#FA8072") ##4682B4
        self.bcheckcpu.grid(row=3, column=1, sticky=W+E+N+S, rowspan=2)
        self.bcheckcpu["command"] = self.checkcpu

        #self.brun['fg'] = 'blue'
        self.brun["command"] = self.start_to_download
        #self.bstop['fg'] = 'red'
        self.bstop["command"] = self.connect_to_dbg

        self.current_process = 0
        self.HexFile = ''

    def check_files(self):
        if len(self.dl_list) == 0:
            messagebox.showerror("Error", "No downloader.exe found")
            print("EXIT")
            self.closeWin()

    def terminate_all_process(self):
        if hasattr(self, "current_process") and type(self.current_process) is subprocess.Popen:
            try:
                self.current_process.terminate()
                self.current_process.wait()
            except OSError as e:
                print(e)

        if hasattr(self, "current_process2") and type(self.current_process2) is subprocess.Popen:
            try:
                self.current_process2.terminate()
                self.current_process2.wait()
            except OSError as e:
                print(e)

        if hasattr(self, "current_process3") and type(self.current_process3) is subprocess.Popen:
            try:
                self.current_process3.terminate()
                self.current_process3.wait()
            except OSError as e:
                print(e)

        if hasattr(self, "current_process4") and type(self.current_process4) is subprocess.Popen:
            try:
                self.current_process4.terminate()
                self.current_process4.wait()
            except OSError as e:
                print(e)

        if hasattr(self, "current_process5") and type(self.current_process5) is subprocess.Popen:
            try:
                self.current_process5.terminate()
                self.current_process5.wait()
            except OSError as e:
                print(e)

        os.system('tasklist|find /i "ICEman.exe" && taskkill /f /t /im ICEman.exe')
        os.system('tasklist|find /i "nds32le-elf-gdb.exe" && taskkill /f /t /im nds32le-elf-gdb.exe')

    def closeWin(self):
        self.terminate_all_process()
        os._exit(1)


    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack(fill=BOTH, expand=1)
        main_frame = Frame(master)
        main_frame.pack(fill="y", expand=1)
        self.createWidgets(main_frame)
        self.dl_thread = 0

        master.protocol('WM_DELETE_WINDOW', self.closeWin)

        threading.Thread(target=self.check_files).start()


if __name__=="__main__":

    print('platform : [{}]'.format(platform.platform()))
    print('platform version : [{}]'.format(platform.version()))
    print('platform architecture : [{}]'.format(platform.architecture()))
    print('platform machine : [{}]'.format(platform.machine()))
    print('platform node : [{}]'.format(platform.node()))
    print('platform processor : [{}]'.format(platform.processor()))
    print('platform system : [{}]'.format(platform.system()))
    #print('uname : [{}]'.format(platform.uname()))

    root = Tk()
    root.title("MV ADS downloader v%s"%(__version__))
    try:
        root.iconbitmap('downloader.ico')
    except Exception as e:
        print(e)
    #lock the root size
    root.resizable(False,False)
    root.lift()

    app = Application(master=root)

    #to minimize the console windows
    ctypes.windll.user32.ShowWindow(ctypes.windll.kernel32.GetConsoleWindow(), 6)

    app.mainloop()
