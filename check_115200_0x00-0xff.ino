/*
 * target の RS-232C データ送出能力をテストするプログラム
 * 入力
 *   target が送出する 0x00-0xFF の循環データをシリアルポートに入力
 * 出力
 * 　シリアルポート
 * 　　"G:\n"   0x00-0xFF の 256byte が正常に受信できた場合
 * 　　"EA:\n"　想定外のデータの受信(0x00以外)
 * 　　"EB:\n"  想定外の 0x00 の受信
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // opens serial port, sets data rate
  pinMode(LED_BUILTIN, OUTPUT);
}

int state = 0;
unsigned char lastData;
int lightState = 0;

int goodCount = 0;    // 将来使う予定
int totalCount = 0;   // 将来使う予定
int errorCount = 0;   // 将来使う予定

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() == 0);

  ProcData();
}

void ProcData() {
  int data;
  
  data = Serial.read();

  switch(state) {
    case 0:   // state is IDLE
      if (0x00 == data) {
        state = 1;  // state is DATA
        lastData = data;
      }
      break;
    case 1:   // state is DATA
      if (0x00 == data) {
        if (0xff == lastData) {
          goodCount += 1;
          totalCount += 1;
          lastData = data;
          Serial.print("G:\n");
          if (lightState == 0) {
            digitalWrite(LED_BUILTIN, HIGH);
            lightState = 1;
          } else {
            lightState = 0;
            digitalWrite(LED_BUILTIN, LOW);
          }
        } else {
          errorCount += 1;
          totalCount += 1;
          lastData = data;
          Serial.print("EB:\n");
        }
      } else {
        if (data - 1 == lastData) {
          lastData = data;
        } else {
          errorCount += 1;
          totalCount += 1;
          state = 0;
          Serial.print("EA:\n");
        }
      }
      break;
  }
}

