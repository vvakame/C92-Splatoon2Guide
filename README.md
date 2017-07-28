# C92-Android [![CircleCI](https://circleci.com/gh/TechBooster/C92-Android.svg?style=svg&circle-token=e510d12baf99365966c6b219d4abfe2d77431560)](https://circleci.com/gh/TechBooster/C92-Android)

- CI: https://griflet.net/github/TechBooster/C92-Android/
  - はじめてアクセスする場合は下のリンクから招待コードを入力してプロジェクトに参加してください
    - https://griflet.net/project/uuid/a07f873d-af32-4cfc-841a-e23af4d7939d/eic
    - 招待コード: EimaiNg7
  - よく分からなかったら @dmiyakawa に連絡してください。


## この本のビルドの仕方

細かい準備(TeX入れたり)は[『技術書をかこう！』](https://github.com/TechBooster/C89-FirstStepReVIEW-v2)に準じます。

TeXの導入をしない場合でもHTML出力は可能です。Dockerコンテナでビルドすることもできます。

## 執筆環境の準備

本書は[Atom](https://atom.io/)で[language-review](https://atom.io/packages/language-review)と[linter-redpen](https://atom.io/packages/linter-redpen)を導入している前提です。
内部的に[RedPen](http://redpen.cc/)を利用するため、 `brew install redpen` とかしておいてください。

Atom以外の環境の場合、[prh](https://github.com/vvakame/prh)または[reviewjs-prh](https://github.com/vvakame/reviewjs-prh)とRedPenを自力でなんとか頑張って適用してください。

警告やlintのエラーを放置して編集に突入してしまうと @mhidaka が過労で死にます。
RedPenは試験的に導入したため、知見やルールについてまだ固まっていません。
意見・感想・修正案などあればHangoutsかSlackなどでﾓﾐﾓﾐしましょう。

### PDF出力する

rbenvやnodebrewを利用してRubyやNode.jsの準備をしている前提です。
もしそうではない場合、適宜sudoを補うこと。
Node.jsは4.x系以上が必須です。

graphvizを使ったのでbrew install graphvizとかが必要かもしれません。

```
$ gem install bundler
$ git clone git@github.com:TechBooster/C92-Android.git
$ cd C92-Android
$ git submodule init
$ git submodule update
$ npm install
$ npm run pdf
```

### Dockerを使う

TeXの環境構築が困難な場合、一式セットアップ済みの[dockerイメージ](https://registry.hub.docker.com/u/vvakame/review/)を用意してあるので使ってください。
Dockerがうまく動くようになっている場合、以下のコマンドで細かい準備なしにビルドを行うことができます。

```
$ docker pull vvakame/review
$ ./build-in-docker.sh
```

### HTML出力

`npm run web` を実行すると、`publish/`ディレクトリ以下に公開用HTMLファイルおよびcss,画像を出力します。
