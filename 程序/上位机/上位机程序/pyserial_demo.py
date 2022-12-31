import sys
import numpy
import numpy as np
import serial
import serial.tools.list_ports
from PyQt5 import QtWidgets
from PyQt5.QtGui import QPixmap, QIcon, QPalette
from PyQt5.QtWidgets import QMessageBox, QLabel
from PyQt5.QtCore import QTimer, Qt
from matplotlib import pyplot
from PIL import Image
from ui_demo_1 import Ui_Form
import time
import mediapipe as mp
import cv2
import pygame


# 数据记录
box_num = 0


class Pyqt5_Serial(QtWidgets.QWidget, Ui_Form):
    def __init__(self):
        super(Pyqt5_Serial, self).__init__()
        self.timer_send = None
        self.web_label = None
        self.setupUi(self)
        self.init()
        self.setWindowOpacity(0.9)  # 设置窗口透明度
        pe = QPalette()
        self.setAutoFillBackground(True)
        # pe.setColor(QPalette.Window,Qt.white)  # 设置背景色
        # pe.setColor(QPalette.Background,Qt.blue)
        self.setPalette(pe)
        self.setWindowTitle("俄罗斯方块串口小助手")  # 设置窗口名称
        self.setWindowIcon(QIcon("image/mode3.jpg"))  # 设置图标
        self.ser = serial.Serial()
        self.port_check()
        self.reading_flag = False

        # 接收数据和发送数据数目置零
        self.data_num_received = 0
        self.lineEdit.setText(str(self.data_num_received))
        self.data_num_sended = 0
        self.lineEdit_2.setText(str(self.data_num_sended))

    def init(self):
        # 初始化音乐
        pygame.init()
        sound = pygame.mixer.Sound(r"image/video.wav")
        sound.set_volume(1)

        # 串口检测按钮
        self.s1__box_1.clicked.connect(self.port_check)
        self.s1__box_1.setStyleSheet('''QPushButton:hover{background:red;}''')

        # 串口信息显示
        self.s1__box_2.currentTextChanged.connect(self.port_imf)

        # 打开串口按钮
        self.open_button.clicked.connect(self.port_open)
        self.open_button.setStyleSheet('''QPushButton:hover{background:yellow;}''')

        # 关闭串口按钮
        self.close_button.clicked.connect(self.port_close)
        self.close_button.setStyleSheet('''QPushButton:hover{background:green;}''')

        # 发送数据按钮
        self.s3__send_button.clicked.connect(self.data_send)

        # up按钮
        self.Button_up.clicked.connect(self.up)

        # down按钮
        self.Button_down.clicked.connect(self.down)

        # right按钮
        self.Button_right.clicked.connect(self.right)

        # left按钮
        self.Button_left.clicked.connect(self.left)

        # a按钮
        self.Button_a.clicked.connect(self.a)

        # 定时发送数据
        self.timer_send = QTimer()
        self.timer_send.timeout.connect(self.data_send)
        self.timer_send_cb.stateChanged.connect(self.data_send_timer)
        self.gesture_checkBox.stateChanged.connect(self.gesture)
        self.dynamic_checkBox.stateChanged.connect(self.data_send_timer)

        # 定时器接收数据
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.data_receive)

        # 清除发送窗口
        self.s3__clear_button.clicked.connect(self.send_data_clear)

        # 清除接收窗口
        self.s2__clear_button.clicked.connect(self.receive_data_clear)

        # 显示GitHub超链接
        self.web_label.setOpenExternalLinks(True)
        self.web_label.setText(u'<a href="https://github.com/yushiran/2022_BIT_Microcontroller_course_design_yushiran" style="color:#0000ff;"><b> 我们的俄罗斯方块项目资料，欢迎star！ </b></a>')

        # 显示游戏画面
        self.label_3.setPixmap(QPixmap("image/init.jpg"))  # 不断更新图片来显示俄罗斯方块
        self.label_3.setScaledContents(True)

        # 显示手势识别画面
        self.gesture_label.setPixmap(QPixmap("image/gesture.jpg"))
        self.gesture_label.setScaledContents(True)

        # 显示方块设置的图片
        self.mode0_label.setPixmap(QPixmap("image/mode0.jpg"))
        self.mode0_label.setScaledContents(True)
        self.mode1_label.setPixmap(QPixmap("image/mode1.jpg"))
        self.mode1_label.setScaledContents(True)
        self.mode2_label.setPixmap(QPixmap("image/mode2.jpg"))
        self.mode2_label.setScaledContents(True)
        self.mode3_label.setPixmap(QPixmap("image/mode3.jpg"))
        self.mode3_label.setScaledContents(True)
        self.mode4_label.setPixmap(QPixmap("image/mode4.jpg"))
        self.mode4_label.setScaledContents(True)
        self.mode5_label.setPixmap(QPixmap("image/mode5.jpg"))
        self.mode5_label.setScaledContents(True)
        self.mode6_label.setPixmap(QPixmap("image/mode6.jpg"))
        self.mode6_label.setScaledContents(True)

        self.next_mode_label.setPixmap(QPixmap("image/mode0.jpg"))
        self.next_mode_label.setScaledContents(True)
        self.now_mode_label.setPixmap(QPixmap("image/mode0.jpg"))
        self.now_mode_label.setScaledContents(True)

    # 串口检测
    def port_check(self):
        # 检测所有存在的串口，将信息存储在字典中
        self.Com_Dict = {}
        port_list = list(serial.tools.list_ports.comports())
        self.s1__box_2.clear()
        for port in port_list:
            self.Com_Dict["%s" % port[0]] = "%s" % port[1]
            self.s1__box_2.addItem(port[0])
        if len(self.Com_Dict) == 0:
            self.state_label.setText(" 无串口")

    # 串口信息
    def port_imf(self):
        # 显示选定的串口的详细信息
        imf_s = self.s1__box_2.currentText()
        if imf_s != "":
            self.state_label.setText(self.Com_Dict[self.s1__box_2.currentText()])

    # 打开串口
    def port_open(self):
        self.ser.port = self.s1__box_2.currentText()
        self.ser.baudrate = int(self.s1__box_3.currentText())
        self.ser.bytesize = int(self.s1__box_4.currentText())
        self.ser.stopbits = int(self.s1__box_6.currentText())
        self.ser.parity = self.s1__box_5.currentText()

        try:
            self.ser.open()
        except:
            QMessageBox.critical(self, "Port Error", "此串口不能被打开！")
            return None

        # 打开串口接收定时器，周期为2ms
        self.timer.start(2)

        if self.ser.isOpen():
            self.open_button.setEnabled(False)
            self.close_button.setEnabled(True)
            self.reading_flag = True
            self.formGroupBox1.setTitle("串口状态（已开启）")

    # 关闭串口
    def port_close(self):
        self.reading_flag = False
        self.timer.stop()
        self.timer_send.stop()
        try:
            self.ser.close()
        except:
            pass
        self.open_button.setEnabled(True)
        self.close_button.setEnabled(False)
        self.lineEdit_3.setEnabled(True)
        # 接收数据和发送数据数目置零
        self.data_num_received = 0
        self.lineEdit.setText(str(self.data_num_received))
        self.data_num_sended = 0
        self.lineEdit_2.setText(str(self.data_num_sended))
        self.formGroupBox1.setTitle("串口状态（已关闭）")

    # 发送数据
    def data_send(self):
        if self.ser.isOpen():
            input_s = self.s3__send_text.toPlainText()
            if input_s != "":
                # 非空字符串
                if self.hex_send.isChecked():
                    # hex发送
                    input_s = input_s.strip()
                    send_list = []
                    while input_s != '':
                        try:
                            num = int(input_s[0:2], 16)
                        except ValueError:
                            QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                            return None
                        input_s = input_s[2:].strip()
                        send_list.append(num)
                    input_s = bytes(send_list)
                else:
                    # ascii发送
                    input_s = (input_s + '\r\n').encode('utf-8')

                num = self.ser.write(input_s)
                self.data_num_sended += num
                self.lineEdit_2.setText(str(self.data_num_sended))
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    # 接收数据
    def data_receive(self):
        bit = np.zeros((16, 16))  # 初始化二值化数组
        print(self.ser.in_waiting)
        if self.ser.in_waiting >= 38:
            # print(self.ser.in_waiting)
            data_temp = bytes()
            time.sleep(0.08)
            data_temp = data_temp + self.ser.read(self.ser.in_waiting)
            # hex显示
            if self.hex_receive.checkState():
                self.s2__receive_text.insertPlainText(str(data_temp))
            else:
                # 串口接收到的字符串为b'123',要转化成unicode字符串才能输出到窗口中去
                self.s2__receive_text.insertPlainText(data_temp.decode('iso-8859-1'))

            if data_temp[38] == 255:
                for i in range(32):
                    bit_num = i // 2
                    data_bin = bin(data_temp[i])  # 把10进制数变成2进制
                    if i % 2 == 0:
                        num0 = list('{:0>8}'.format(str(data_bin)[2:]))
                        for j in range(len(num0)):
                            if int(num0[j]) > 0:
                                bit[bit_num][j] = 0
                            else:
                                bit[bit_num][j] = 255
                    else:
                        num1 = list('{:0>8}'.format(str(data_bin)[2:]))
                        for k in range(len(num1)):
                            if int(num1[k]) > 0:
                                bit[bit_num][k + 8] = 0
                            else:
                                bit[bit_num][k + 8] = 255
                bit = numpy.repeat(bit, 25, axis=1)
                bit = numpy.repeat(bit, 25, axis=0)
                bit = Image.fromarray(bit)

                pyplot.imsave('image/test.jpg', bit)

                # 记录数据
                global box_num
                score = int(data_temp[35])
                # print('data_temp[34]=', data_temp[34], 'data_temp[35]=', data_temp[35], 'score=', score_temp)
                box_num_temp = int(data_temp[37])
                # print('data_temp[36]=', data_temp[36], 'data_temp[37]=', data_temp[37], 'box_num=', box_num)
                if (box_num_temp != box_num):
                    record(score, box_num_temp)
                    box_num = box_num_temp
                else:
                    pass

                # 不断更新图片来显示下一个俄罗斯方块和当前方块
                next_mode_add = "image/mode"+str(data_temp[33])+".jpg"
                now_mode_add = "image/mode"+str(data_temp[32])+".jpg"
                self.next_mode_label.setPixmap(QPixmap(next_mode_add))
                self.next_mode_label.setScaledContents(True)
                self.now_mode_label.setPixmap(QPixmap(now_mode_add))
                self.now_mode_label.setScaledContents(True)
                # 不断更新图片来显示俄罗斯方块
                self.label_3.setPixmap(QPixmap("image/test.jpg"))
                self.label_3.setScaledContents(True)
                # 统计接收字符的数量
                self.data_num_received += len(data_temp)
                self.lineEdit.setText(str(self.data_num_received))

                # 获取到text光标
                textCursor = self.s2__receive_text.textCursor()
                # 滚动到底部
                textCursor.movePosition(textCursor.End)
                # 设置光标到text中去
                self.s2__receive_text.setTextCursor(textCursor)

        time.sleep(0.08)

    # 定时发送数据
    def data_send_timer(self):
        if self.timer_send_cb.isChecked() or self.dynamic_checkBox.isChecked():
            self.timer_send.start(int(self.lineEdit_3.text()))
            self.lineEdit_3.setEnabled(False)
        else:
            self.timer_send.stop()
            self.lineEdit_3.setEnabled(True)

    def gesture(self):
        cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
        if self.gesture_checkBox.isChecked():
            while True:
                # 定义手 检测对象
                mpHands = mp.solutions.hands
                hands = mpHands.Hands()
                mpDraw = mp.solutions.drawing_utils
                # 读取一帧图像
                success, img = cap.read()
                if not success:
                    continue
                image_height, image_width, _ = np.shape(img)

                # 转换为RGB
                imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

                # 得到检测结果
                results = hands.process(imgRGB)

                if results.multi_hand_landmarks:
                    hand = results.multi_hand_landmarks[0]

                    mpDraw.draw_landmarks(img, hand, mpHands.HAND_CONNECTIONS)

                    # 采集所有关键点的坐标
                    list_lms = []
                    for i in range(21):
                        pos_x = hand.landmark[i].x * image_width
                        pos_y = hand.landmark[i].y * image_height
                        list_lms.append([int(pos_x), int(pos_y)])

                    # 构造凸包点
                    list_lms = np.array(list_lms, dtype=np.int32)
                    hull_index = [0, 1, 2, 3, 6, 10, 14, 19, 18, 17, 10]
                    hull = cv2.convexHull(list_lms[hull_index, :])
                    # 绘制凸包
                    cv2.polylines(img, [hull], True, (0, 255, 0), 2)

                    # 查找外部的点数
                    n_fig = -1
                    ll = [4, 8, 12, 16, 20]
                    up_fingers = []

                    for i in ll:
                        pt = (int(list_lms[i][0]), int(list_lms[i][1]))
                        dist = cv2.pointPolygonTest(hull, pt, True)
                        if dist < 0:
                            up_fingers.append(i)

                    str_guester = get_str_guester(up_fingers, list_lms)

                    if self.ser.isOpen():
                        input_s = str(str_guester)
                        input_s = input_s.strip()
                        send_list = []
                        while input_s != '':
                            try:
                                num = int(input_s[0:2], 16)
                            except ValueError:
                                QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                                return None
                            input_s = input_s[2:].strip()
                            send_list.append(num)
                        input_s = bytes(send_list)
                        self.ser.write(input_s)
                    else:
                        QMessageBox.critical(self, "Port Error", "请先打开串口")
                        pass

                    cv2.putText(img, ' %s' % (str_guester), (90, 90), cv2.FONT_HERSHEY_SIMPLEX, 3, (255, 255, 0), 4,
                                cv2.LINE_AA)

                    for i in ll:
                        pos_x = hand.landmark[i].x * image_width
                        pos_y = hand.landmark[i].y * image_height
                        # 画点
                        cv2.circle(img, (int(pos_x), int(pos_y)), 3, (0, 255, 255), -1)

                cv2.imwrite('image/gesture.jpg', img)
                # 不断更新图片来显示手势
                self.gesture_label.setPixmap(QPixmap("image/gesture.jpg"))
                self.gesture_label.setScaledContents(True)
                key = cv2.waitKey(1) & 0xFF

        else:
            cap.release()

    # 清除显示
    def send_data_clear(self):
        self.s3__send_text.setText("")

    def receive_data_clear(self):
        self.s2__receive_text.setText("")

    # 方块控制
    def up(self):
        if self.ser.isOpen():
            input_s = "u"
            input_s = (input_s + '\r\n').encode('utf-8')
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def down(self):
        if self.ser.isOpen():
            input_s = "d"
            input_s = (input_s + '\r\n').encode('utf-8')
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def left(self):
        if self.ser.isOpen():
            input_s = "l"
            input_s = (input_s + '\r\n').encode('utf-8')
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def right(self):
        if self.ser.isOpen():
            input_s = "r"
            input_s = (input_s + '\r\n').encode('utf-8')
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def a(self):
        if self.ser.isOpen():
            input_s = "a"
            input_s = (input_s + '\r\n').encode('utf-8')
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    # 方块预设
    def mode0(self):
        if self.ser.isOpen():
            input_s = "0"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def mode1(self):
        if self.ser.isOpen():
            input_s = "1"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def mode2(self):
        if self.ser.isOpen():
            input_s = "2"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def mode3(self):
        if self.ser.isOpen():
            input_s = "3"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def mode4(self):
        if self.ser.isOpen():
            input_s = "4"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def mode5(self):
        if self.ser.isOpen():
            input_s = "5"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass

    def mode6(self):
        if self.ser.isOpen():
            input_s = "6"
            input_s = input_s.strip()
            send_list = []
            while input_s != '':
                try:
                    num = int(input_s[0:2], 16)
                except ValueError:
                    QMessageBox.critical(self, 'wrong data', '请输入十六进制数据，以空格分开!')
                    return None
                input_s = input_s[2:].strip()
                send_list.append(num)
            input_s = bytes(send_list)
            self.ser.write(input_s)
        else:
            QMessageBox.critical(self, "Port Error", "请先打开串口")
            pass


def record(score, box_num):
    file = open(r"record.txt", "a", encoding='utf-8')
    file.write(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())))
    file.write('  当前获得分数：')
    file.write(str(score))
    file.write('  当前下落方块个数：')
    file.write(str(box_num))
    file.write('\n')
    file.close()
    return


def get_angle(v1, v2):
    angle = np.dot(v1, v2) / (np.sqrt(np.sum(v1 * v1)) * np.sqrt(np.sum(v2 * v2)))
    angle = np.arccos(angle) / 3.14 * 180

    return angle


def get_str_guester(up_fingers, list_lms):
    if len(up_fingers) == 1 and up_fingers[0] == 8:

        v1 = list_lms[6] - list_lms[7]
        v2 = list_lms[8] - list_lms[7]

        angle = get_angle(v1, v2)

        str_guester = "1"

    elif len(up_fingers) == 2 and up_fingers[0] == 8 and up_fingers[1] == 12:
        str_guester = "2"

    elif len(up_fingers) == 2 and up_fingers[0] == 4 and up_fingers[1] == 20:
        str_guester = "6"

    elif len(up_fingers) == 3 and up_fingers[0] == 8 and up_fingers[1] == 12 and up_fingers[2] == 16:
        str_guester = "3"

    elif len(up_fingers) == 3 and up_fingers[0] == 4 and up_fingers[1] == 8 and up_fingers[2] == 12:

        dis_8_12 = list_lms[8, :] - list_lms[12, :]
        dis_8_12 = np.sqrt(np.dot(dis_8_12, dis_8_12))

        dis_4_12 = list_lms[4, :] - list_lms[12, :]
        dis_4_12 = np.sqrt(np.dot(dis_4_12, dis_4_12))

        if dis_4_12 / (dis_8_12 + 1) < 3:
            str_guester = "7"

        else:
            str_guester = "7"

    elif len(up_fingers) == 4 and up_fingers[0] == 8 and up_fingers[1] == 12 and up_fingers[2] == 16 and up_fingers[3] == 20:
        str_guester = "4"

    elif len(up_fingers) == 5:
        str_guester = "5"

    elif len(up_fingers) == 0:
        str_guester = "0"

    else:
        str_guester = "0"

    return str_guester


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    myshow = Pyqt5_Serial()
    myshow.show()
    sys.exit(app.exec_())
