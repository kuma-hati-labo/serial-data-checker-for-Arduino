# serial-data-checker-for-Arduino
Arduino で動くシリアルデータチェックプログラム 

Arduino UNO R3 のシリアルポートに 115200bps/8N1 で 0x00-0xff の循環データを入力し、正しく受信できているかをチェックする

受信結果はシリアルポートから出力する  
　　"G:\n"   0x00-0xFF の 256byte が正常に受信できた場合  
 　"EA:\n"　想定外のデータの受信(0x00以外)  
 　"EB:\n"  想定外の 0x00 の受信  
  
