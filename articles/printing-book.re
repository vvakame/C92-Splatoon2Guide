={printing-book} 入稿戦記

本書の目的は@<chapref>{preface}で書いたとおり、フリーなツールやフォントだけで印刷所に入稿できるのか？の検証なのでやっていく。
入稿用PDFの作成は@<href>{https://hub.docker.com/r/vvakame/review/}で作る。
TeX Live@<fn>{texlive}とNotoフォント@<fn>{noto-font}を利用する。

//footnote[texlive][@<href>{https://www.tug.org/texlive/}]
//footnote[noto-font][@<href>{https://www.google.com/get/noto/}]

=== 07/30 12:32 原稿がとりあえずひととおり終わった

2日前の金曜日の19:04に最初のコミットがあって、日曜日の12:32にとりあえず23P書き終えた。
これからが真の戦いだ…。

オフセットはもう間に合わないのでオンデマンド印刷だ！

=== 07/30 15:19 データ作るぞ

某アレのソレのためにTechBoosterの一部の人間が弊社に集まってきている。

C92で出すRe:VIEW本@<fn>{c92-review}を読むと、フォントの埋込とPDF/Xに変換とグレースケール化をやったほうがいいらしい。

#@# prh:disable
//footnote[c92-review][@<href>{https://github.com/TechBooster/C89-FirstStepReVIEW-v2}]

フォントの埋込については、Re:VIEWのDockerイメージがデフォルトでNotoフォントを埋め込んでくれるので何も考える必要はない。

近くにtakahashimさんが居たので、「入稿ってPDF/Xでないとだめなんですかね？」と聞いたら「は？」といわれたので別に必須ではないらしい。

日光企画さんのFAQ@<fn>{nikko-faq}によると、RGBなデータを入稿してもCMYK化してくれるそうなので印刷品質にあまりこだわらない技術書としてはそれでいいかという気持ち。

//footnote[nikko-faq][@<href>{http://www.nikko-pc.com/off-faq/off-faq.html}]

グレースケール化は行ってから提出したほうが仕上がりがイメージできそうなので適当にやることにする。
ぐぐった結果、ImageMagickでできるよ！とStackOverflowに書いてあった@<fn>{so-grayscale}ので試してみたらラスタライズしてグレスケしてPDFにしてくれて文字がクッソ荒くなった。
おとなしくGhostscriptでやることにする。

//footnote[so-grayscale][@<href>{https://superuser.com/questions/104656/}]

調べるとGhostscriptには@<i>{Creating a PDF/X-3 document}というドキュメントがあったのでそのオプションの組み合わせを使ってみる。
印刷業界はAdobe様が吐いたPDF以外信用しない文化らしいので、名目上の規格があってたからとそれでよいわけではないらしい。
よって、この配慮に意味があるかは不明だ。

利用するシェルスクリプトは3点。
Re:VIEWのreview-pdfmakerを使ってPDFを作るところまでは割愛する。

//emlist[build-in-docker.sh]{
#@mapfile(../build-in-docker.sh)
#!/bin/bash -eux

docker run -t --rm \
  -v $(pwd):/book vvakame/review \
  /bin/bash -ci "cd /book && ./setup.sh && npm run pdf && ./grayscale.sh"
#@end
//}

//emlist[setup.sh]{
#@mapfile(../setup.sh)
#!/bin/bash -eux

rm -rf node_modules
# --unsafe-perm はrootでの実行時(= docker環境)で必要 非root時の挙動に影響なし
npm install --unsafe-perm
git submodule init && git submodule update
#@end
//}

//emlist[grayscale.sh]{
#@mapfile(../grayscale.sh)
#!/bin/bash -eux

gs \
  -sOutputFile=articles/C92-Splatoon2Guide-gray.pdf \
  -sDEVICE=pdfwrite \
  -dPDFX \
  -dCompatibilityLevel=1.3 \
  -sColorConversionStrategy=Gray \
  -dProcessColorModel=/DeviceGray \
  -dNOPAUSE \
  -dBATCH \
  articles/C92-Splatoon2Guide.pdf
#@end
//}

これでグレースケール化済PDFが作成できた。

=== 07/30 19:38 A5版に変える

羊がA5版でよくない？と言ったのでA5記念日。

C91のDDD本@<fn>{ddd-book}が印刷版がA5版だったらしいので設定ファイルをにゅるっと移植@<fn>{b5-to-a5}。
過去の資産があるって素晴らしい！

//footnote[ddd-book][@<href>{https://techbooster.booth.pm/items/392260}]
//footnote[b5-to-a5][@<href>{https://github.com/vvakame/C92-Splatoon2Guide/commit/ee3c4ac8776f8162e5ca7e04c2f32474f7834e5c}]

Nintendo Switchで撮影したスクリーンショット、MBPに移す方法がない。
Amazonで@<href>{https://www.amazon.co.jp/gp/product/B071HT25GP/}を注文したんだけどまだ発送されない。
旧MBPにはSDのスロットがあるのでアダプタを家のどこかから発掘して頑張るしかなさそう。
SwitchにDropbox搭載してくれ〜〜〜。

=== 07/30 20:01 日光企画さんに見積もり依頼をかける

表紙データを羊が発注してくれて、イラストレーターさんからのあがりは水曜（08/02）予定だそうだ。
このクソスケジュールで請けてくれるのすごいと思う。

印刷キューがどうなってるかわからないので電話かメールで印刷所に予約申込の連絡をしろと羊にいわれる。
電話は苦手なのでめるめるします…。
普通に見積もりフォームがあってこれ経由でいいらしい。

部数30部くらいでいい？と羊に相談したら「その葛藤が技術書典参加サークルの葛藤だよ！」といわれた。
確かにそうだなぁ、と思ってとりあえず100部刷ることにした。
みんな100とか200とかバンバン刷ってほしい。
見積もりの依頼を送った！しばらくの間、毎日メールをチェックしなければならない。
#@# TODO estimate.png として見積もりフォーム入力内容を保存

=== 07/31 23:58 グレースケール化したときにインクの色が全然出ない

やっとSwitchで撮ったスクショのデータを取り出せたので文中に張り込んでみる。
なかなかよい。
グレースケール化もしておくか！と思って試してみたら、黄緑とオレンジのインクの組み合わせだと両方同じ色に見える！
さらに、Skitch@<fn>{skitch}で入れた矢印が全然見えない！
ぐぬぬ、文字は白枠がついているのでしっかり見える…。
どーすんだこれ。

とりあえずインクの色についてはSplatoon2は色覚異常の人のための色覚サポート機能があるのでONにして試してみた。
6戦ほどしてみたが黄と紫のインクの組み合わせに固定されるようだ。
こっちはグレースケールにしてもちゃんと見える。
アクセシビリティに配慮されたゲームだ…！

矢印に白枠つける方法がわからなかったので線の太さを変えた白矢印の上に赤矢印を乗せてごまかす。
めんどい作業だ。
フリーで操作しやすい画像に注釈入れるツールがほしいな。
実はAdobe Creative Cloud コンプリート12ヶ月版を買ってあるのでイラストレーター使えばいいんだけども。

//footnote[skitch][@<href>{https://evernote.com/intl/jp/products/skitch}]

=== 08/01 10:31 見積もりのレスポンスを待ってたの？

//noindent
muo「いつまで原稿粘るの？」@<br>{}
vv「見積もりのレスポンスが返ってこないねんなーまだ」@<br>{}
羊「あっ。かえってこないよ」@<br>{}
vv「えっ」@<br>{}
羊「クソ忙しい時期にレスポンス返ってくるわけないでしょ」@<br>{}
vv「わかりみがある」@<br>{}
羊「そのまま入稿するか不安なら電話するんやで」@<br>{}
vv「じゃあ表紙データもらい次第ぶっこめるよう本文も準備しておけってこと？」@<br>{}
羊「むしろ表紙データもらったらぶっこめるよう本文を先に作っとく、が正しい極道」@<br>{}
vv「納得感高い」@<br>{}
羊「先に本文いれて輪転機まわすだけの状態にするもしくは本文の輪転機をまわしておく、までレベルアップ方法がある」@<br>{}
vv「0電話を目指したい…」@<br>{}
やぎ「物理世界は過酷だ」

=== 08/02 00:41 ページ数の調整に追われる

水曜日（今日だ）に入稿できるよう、校正を終わらせていきたい。
現在33ページなので32ページに削減したい…。
ちょびっとはみ出てページ数増えているところやタイトル行が2行になっているところを直したら29ページになった。
げせぬ…。

料金表を見るとページ数は8の倍数ではなく、4の倍数でよいらしい。
ならば28ページか32ページに着地させるのが妥当っぽい。

各章の末尾に半ページくらいの白があるところがちょいちょいあるのも気になる。
白の部分が1/4ページ未満になるように頑張りたい。

いつも羊は苦労しているのだなぁ。
いやぁ…人にやってもらえるって…最高やな！（クズ並の感想）

=== 08/02 02:02 表紙データを受領する

五体投地し感謝の祈りを捧げる。

PSDファイルをぺろんと貰ったので日光企画さんの表紙用トンボテンプレートとmergeする必要があるらしい。
背幅の計算方法は 表紙込み総ページ数×本文用紙の厚さ＝背幅（mm） だそうだ。
（4+32）×（上質紙90Kg 0.063mm）＝2.268mmとなった。
羊情報によると背に何か書けるのは7mm超えてからだそうだ。
まぁ今回は背の部分に着色したりする気がないしあまり細かく考えなくてよいだろう。
#@# TODO sinmetal的には背表紙のデータの作り方が不思議だったらしい

裏表紙に何も添え物がないのは寂しい気がするが変にいじるのも気が引ける。
TechBoosterはロゴがあるのでこういう時便利だな…。
ひかる黄金わかめ帝国にも何かほしい気がする。

トンボテンプレートがEPSとPSD（CMYK）で提供されてるんだけど両方GIMPでは開けなさそうっぽい…。
InkScapeも試してみたけどeps食わせると音もなく死ぬ。
もうAdobeの月980円プラン@<fn>{not-980}契約して一瞬Photoshop CC使えばいいんじゃないかな…という気持ちになってきた。

//footnote[not-980][後で知ったところによると実は月額が980円というだけで年契約必須途中解約は残期間も50%取られるシステムらしい]

=== 08/02 20:21 Affinity Designを使う

grapswizからAffinity Design@<fn>{affinity-design}がお勧めっすよ！と教えてもらう。
買い切りで¥6,000らしいので、入稿データ作ってみて怒られなかったらお買上げしよう。
フリーなツールでとは… という気もするが入稿が優先だ！時間を金で買うんだ！続きは読者への課題とする！

//footnote[affinity-design][@<href>{https://affinity.serif.com/ja-jp/designer/}]

作ったデータを羊に見せたところ、表紙と裏表紙が逆であると指摘をうける。
左綴じだったっけ…？
他の技術書を確認するとたしかに左綴じで、右側が表紙で左側が裏表紙だ。
危ない。

裏表紙どうしようかなーと思って表紙絵を黒く塗りつぶした画像を小さく左下に置いたところ、少女祈祷中…感が出てしまう。
羊が「裏表紙、表紙を拡大してものくろにしてみ。めっちゃいいかんじになるで。モノクロは薄めにな。」というのでやってみると次郎感があってよい。
裏表紙のサークル名のフォントはmacOSバンドルの紫B丸ゴシックにした。
やっぱりサークルのロゴがあると便利そうなのでランサーズかなんかを試してみるのもよいのかもしれない。

=== 08/02 21:41 入稿する

表紙データはAffinity Designで生成した350DPI CMYK EPS形式（だと思っている）。
本文データはRe:VIEWで生成したRGBカラーなPDFを入稿する。
