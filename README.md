# 負けたくない！Splatoon2 [![CircleCI]([![CircleCI](https://circleci.com/gh/vvakame/C92-Splatoon2Guide.svg?style=svg)](https://circleci.com/gh/vvakame/C92-Splatoon2Guide))

## この本のビルドの仕方

細かい準備(TeX入れたり)は[『技術書をかこう！』](https://github.com/TechBooster/C89-FirstStepReVIEW-v2)に準じます。

TeXの導入をしない場合でもHTML出力は可能です。Dockerコンテナでビルドすることもできます。

## 執筆環境の準備

本書は[Atom](https://atom.io/)で[language-review](https://atom.io/packages/language-review)と[linter-redpen](https://atom.io/packages/linter-redpen)を導入している前提です。
内部的に[RedPen](http://redpen.cc/)を利用するため、 `brew install redpen` とかしておいてください。

Atom以外の環境の場合、[prh](https://github.com/vvakame/prh)または[reviewjs-prh](https://github.com/vvakame/reviewjs-prh)とRedPenを自力でなんとか頑張って適用してください。

警告やlintのエラーを放置して編集に突入してしまうと編集担当が過労で死にます。
RedPenは試験的に導入したため、知見やルールについてまだ固まっていません。
意見・感想・修正案などあればIssueやpull requestでお知らせください。

### PDF出力する

rbenvやnodebrewを利用してRubyやNode.jsの準備をしている前提です。
必要であれば適宜sudoを補うこと。
Node.jsは6.x系以上が必須です。

```
$ gem install bundler
$ git clone https://github.com/vvakame/C92-Splatoon2Guide.git
$ cd C92-Splatoon2Guide
$ git submodule init && git submodule update
$ npm install
$ npm run pdf
```

### Dockerを使う

TeXの環境構築が困難な場合、一式セットアップ済みの[dockerイメージ](https://registry.hub.docker.com/u/vvakame/review/)を用意してあるので使ってください。
Dockerがうまく動くようになっている場合、以下のコマンドで細かい準備なしにビルドを行うことができます。

```
$ ./build-in-docker.sh
```
