#ifndef INC_UNI_NLU_CONTENT_H_
#define INC_UNI_NLU_CONTENT_H_

typedef struct {
  uni_u32 key_word_hash_code; /* 存放识别词汇对应的hashcode */
  uni_u8  nlu_content_str_index; /* 存放nlu映射表中的索引，实现多个识别词汇可对应同一个nlu，暂支持256条，如果不够换u16 */
  char    *hash_collision_orginal_str /* 类似Java String equal，当hash发生碰撞时，赋值为识别词汇，否则设置为NULL */;
} uni_nlu_content_mapping_t;

enum {
  eCMD_wakeup_uni,
  eCMD_exitUni,
  eCMD_TurnOn,
  eCMD_TurnOff,
  eCMD_TurnLeft,
  eCMD_TurnRight,
};

const char* const g_nlu_content_str[] = {
[eCMD_wakeup_uni] = "{\"asr\":\"小车小车\",\"cmd\":\"wakeup_uni\",\"pcm\":\"[103, 104]\"}",
[eCMD_exitUni] = "{\"asr\":\"不是叫你\",\"cmd\":\"exitUni\",\"pcm\":\"[105]\"}",
[eCMD_TurnOn] = "{\"asr\":\"打开小车\",\"cmd\":\"TurnOn\",\"pcm\":\"[107]\"}",
[eCMD_TurnOff] = "{\"asr\":\"关闭小车\",\"cmd\":\"TurnOff\",\"pcm\":\"[108]\"}",
[eCMD_TurnLeft] = "{\"asr\":\"左转\",\"cmd\":\"TurnLeft\",\"pcm\":\"[109]\"}",
[eCMD_TurnRight] = "{\"asr\":\"右转\",\"cmd\":\"TurnRight\",\"pcm\":\"[110]\"}",
};

/*TODO perf sort by hashcode O(logN), now version O(N)*/
const uni_nlu_content_mapping_t g_nlu_content_mapping[] = {
  {2708576026U/*小车小车*/, eCMD_wakeup_uni, NULL},
  {2692455491U/*小车你好*/, eCMD_wakeup_uni, NULL},
  {2835569027U/*你好小车*/, eCMD_wakeup_uni, NULL},
  {110232650U/*不是叫你*/, eCMD_exitUni, NULL},
  {3432415238U/*打开小车*/, eCMD_TurnOn, NULL},
  {3269679032U/*请开车*/, eCMD_TurnOn, NULL},
  {2438772456U/*开车*/, eCMD_TurnOn, NULL},
  {2399533247U/*启动*/, eCMD_TurnOn, NULL},
  {2397720458U/*发车*/, eCMD_TurnOn, NULL},
  {2301402092U/*启动小车*/, eCMD_TurnOn, NULL},
  {2491342265U/*关闭小车*/, eCMD_TurnOff, NULL},
  {3220404508U/*请关闭*/, eCMD_TurnOff, NULL},
  {2389497932U/*关闭*/, eCMD_TurnOff, NULL},
  {2385118865U/*停车*/, eCMD_TurnOff, NULL},
  {3216025441U/*请停车*/, eCMD_TurnOff, NULL},
  {3341878946U/*把车停下*/, eCMD_TurnOff, NULL},
  {2435286915U/*左转*/, eCMD_TurnLeft, NULL},
  {2540675241U/*向左转*/, eCMD_TurnLeft, NULL},
  {2398733358U/*右转*/, eCMD_TurnRight, NULL},
  {2504121684U/*向右转*/, eCMD_TurnRight, NULL},
};

#endif
