void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  Serial.begin(9600);
}

int sayi_kimde(){   //sayıyı alan oyuncunun pin numarasını değer olarak döndürüyor. sayıyı alan kimse yoksa 0 döndürüyor.
  if(digitalRead(2) == HIGH){
    return 2;
  }
  else if(digitalRead(3) == HIGH){
    return 3;
  }
  else if(digitalRead(4) == HIGH){
    return 4;
  }
  else if(digitalRead(5) == HIGH){
    return 5;
  }
  else{
    return 0;
  }
}


int game(int ortadaki_sayi, int oyuncular[4][3]){  //oyunun genel mantığını içeren fonksiyon budur.
  int sayiyialan = 0;   //sayi_kimde() fonksiyonundan dönen değeri tutacak olan değişken.
  while(1){
    int k = 0;
    Serial.println(ortadaki_sayi); //bu değer her tur başlangıcında fonksiyona 0 olarak giriliyor.(oyun 9 turdan oluşuyor)
    if(ortadaki_sayi < 5){ // ortadaki_Sayi < 5 ise ortadaki_sayinin her 4 saniyede bir artsın. ve her 50 ms de bir butona basan birisi var mı kontrol edelim.
      while(k < 80){
        sayiyialan = sayi_kimde();
        if(sayiyialan != 0){
          delay(500);  //butona basıldığında 500 ms delay koyduk çünkü el butondan çekilene dek yüzlerce kez basılmış gibi algılanmasını engellemek için.
          break;
        }
        k++;
        delay(50);
      }  
    }
    else if(5 <= ortadaki_sayi && ortadaki_sayi < 10){ //yukarıdaki if ten tek farkı sayı 5 ile 10 arasındaysa 1,5 saniyelik bekleme süresi veriyor olması.
      while(k < 30){
        sayiyialan = sayi_kimde();
        if(sayiyialan != 0){
          delay(500);
          break;
        }
        k++;
        delay(50);
      }
    }
    else{
      while(k < 4){   //if elselerden tek farkı 200 ms bekleyerek sayıyı büyütüyor olması.
        sayiyialan = sayi_kimde();
        if(sayiyialan != 0){
          delay(500);
          break;
        }
        k++;
        delay(50);
      }
    }
    if(sayiyialan != 0){ //sayi_kimde() fonksiyonu 0 döndürmemiş ise bir oyuncu butona basmış demektir. ortadaki_sayi nin sürekli arttığı while döngüsünden çıkmak gerekir.
      break;}
    ortadaki_sayi++;
  }
  for(int i = 0; i <= 3; i++){
    if(oyuncular[i][0] == sayiyialan){  //[i][0] = pin numarası  ,  [i][1] = kalan hak sayısı,  [i][2] =  toplam puanı
      if(oyuncular[i][1] == 0){
        game(ortadaki_sayi+1,oyuncular);  //eğer butona basan kişinin hakkı kalmamış ise sayıyı ona veremeyiz oyuna kaldığımız yerden devam etmemiz gerekir.
      }
      else{
        oyuncular[i][2] += ortadaki_sayi;  //butona basan oyuncunun kalan hakkı 0 değil ise sayıyı puan olarak ver ve kalan hakkını 1 azalt.
        oyuncular[i][1]--;
        return i; //i yi döndürme sebebimiz loop() içerisinde sayiyi olan oyuncunun adını yazdırabilmek için kullanacak olmamızdır.
      }
    }
  }
}

void tablo_yaz(int oyuncular[4][3]){ //bu fonk sadece kalan hak sayısını ve toplam puanını sırasıyla (1)(33) şeklinde yazıyor her oyuncunun
  for(int i = 1; i<=4; i++){
    Serial.print("(hak)(puan)\t\t");
  }
  Serial.println();
  for(int i = 0; i<=3; i++){
    Serial.print("  ");
    Serial.print(oyuncular[i][1]);
    Serial.print("\t");
    Serial.print(oyuncular[i][2]);
    Serial.print("\t\t");
  }
  Serial.println();
}

void loop() {
  String oyuncu1, oyuncu2, oyuncu3, oyuncu4;
  Serial.println("\t\t    THIRST FOR RISE"); //oyun başlangıcında oyunun adını yazmak istedik.
  Serial.println("\t\t(GROUP 4 ARDİUNO PROJECT)");
  Serial.print("Oyuncu1 için isim giriniz(4-8 karakter): ");
  while (!Serial.available()) {}
  oyuncu1 = Serial.readStringUntil('\n');
  Serial.println(oyuncu1);  // sırasıyla her oyuncu için isim girilmesini istiyoruz.(4-8 karakter sınırlamasının sebebi skor tablosunda görsel düzeni korumak istememiz)

  Serial.print("Oyuncu2 için isim giriniz:(4-8 karakter) ");
  while (!Serial.available()) {}
  oyuncu2 = Serial.readStringUntil('\n');
  Serial.println(oyuncu2);
  
  Serial.print("Oyuncu3 için isim giriniz:(4-8 karakter) ");
  while (!Serial.available()) {}
  oyuncu3 = Serial.readStringUntil('\n');
  Serial.println(oyuncu3);
  
  Serial.print("Oyuncu4 için isim giriniz:(4-8 karakter) ");
  while (!Serial.available()) {}
  oyuncu4 = Serial.readStringUntil('\n');
  Serial.println(oyuncu4);
  
  delay(1000); //isimler alındı oyun başlamadan önce 1 saniye bekleme süresi

  int oyun_dongusu = 1; //be değişken oyunun kaçınca turda olduğunu tutuyor.
  int oyuncular[4][3] = {{2,3,0},{3,3,0},{4,3,0},{5,3,0}};  //sırasıyla bağlı olduğu pin - kalan hak sayısı - toplam punaı
  while(oyun_dongusu < 10){  //oyun 9 tur dönsün istiyoruz keyifli bir deneyim sunabilmek için
    Serial.print(oyun_dongusu);
    Serial.println(".tur baslıyor");
    delay(1000);
    int sayiyi_alan = game(0,oyuncular);  //bir oyuncu butona basana dek bu satır çalışıyor. butona basıldığında basan kişi hakkı 0 değil ise puan kazanıyor ve hakkı 1 azalıyor. en son ise game() sayıyı alan oyuncunun pin numarasının 1 eksiğini döndürüyor.
    switch(sayiyi_alan){//sayiyi _ alan oyuncunun ismini yazalım.
      case 0:
        Serial.println("Sayıyı "+ oyuncu1 +" aldı.");
        break;
      case 1:
        Serial.println("Sayıyı "+ oyuncu2 +" aldı.");
        break;
      case 2:
        Serial.println("Sayıyı "+ oyuncu3 +" aldı.");
        break;
      case 3:
        Serial.println("Sayıyı "+ oyuncu4 +" aldı.");
        break;
    }
    delay(1000);//sayıyı alan oyuncuyu yazdık şimdi skor tablosunu yazmadan önce 1 sn delay.
    Serial.println("\n");
    Serial.println("\t\t\t\t  SKOR TABLOSU");
    Serial.println();
    Serial.println("  "+oyuncu1+ "                   " + oyuncu2 + "                   "+ oyuncu3 + "                   "+ oyuncu4);
    tablo_yaz(oyuncular);
    delay(3000); //skor tablosunun okunabilmesi için 3 sn delay.
    Serial.println("\n");
    oyun_dongusu++;// tur sayısı +1.

  }
  while(true){}
}