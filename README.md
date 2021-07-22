# とは
かたりさん作の[DOL Macro Controller](https://ux.getuploader.com/DOL_Macro)と夜綱さん作の[ORCA GC Controller](https://www.dropbox.com/sh/8a7bms06wmhnlxr/AADWmI8nNTtx7VraTaGLY2oPa/%E3%83%9D%E3%82%B1%E3%83%A2%E3%83%B3/%E6%AF%94%E8%BC%83%E7%9A%84%E5%AE%9F%E7%94%A8%E6%80%A7%E3%81%AE%E3%81%82%E3%82%8B%E3%83%84%E3%83%BC%E3%83%AB/ORCA%20GC%20Controller)に対応するGC自動化用Arduinoファームウェアです。
## つかいかた
Arduino IDEをインストール後,「ツール→ライブラリを管理」から[nicohood/Nintendoライブラリ](https://github.com/NicoHood/Nintendo)(2枚目中央のライブラリ)をインストールします。

![image1](https://assets.st-note.com/production/uploads/images/46427464/picture_pc_2e562a7018659842e390ea9b2eab9ca0.png)
![image2](https://assets.st-note.com/production/uploads/images/46427555/picture_pc_7ac12adf8ace1f7c9470dbe3e6a72b99.png)

後は同じく「ツール→ボード,シリアルポート」を自分の使っているArduinoのものに設定し「マイコンボードに書き込む」を選択すれば書き込まれます。
## 個々で調整すべき箇所
.inoファイルで各自編集してもらいたいポイントは3つあります。ご自身の環境に合わせて調整してください。

・5行目 GCへ接続するデジタルピンの番号 デフォルト5番ピン

・7行目 サーボを接続するPWMに対応したデジタルピンの番号(Arduino UNOの場合は3,5,6,9,10,11ピンのどれか) デフォルト6番ピン

・196行目 リセット押下時のサーボの角度 デフォルト65度

## すぺしゃるさんくす
バグ改善,ソフト作成で協力していただいたかたりさん,夜綱さん,つきのきさんに感謝を
