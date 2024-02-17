[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver GT30L32S4W

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/gt30l32s4w/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

GT30L32S4Wは、12×12ドットマトリクス、16×16ドットマトリクス、24×24ドットマトリクス、および32×32ドットマトリクスを含む漢字ライブラリチップです。 GB2312 国家標準中国語文字 (国家情報標準化委員会からの法的認可を含む) および ASCII 文字をサポートします。 配置形式は横型です。 ユーザーは、このマニュアルで提供されている方法を使用して、文字内部コードを通じてチップ内の文字マトリクスのアドレスを計算し、このアドレスから文字マトリクス情報を継続的に読み取ることができます。

LibDriver GT30L32S4W は、LibDriver によって起動される GT30L32S4W のフル機能ドライバです。ドットマトリックス読み取り機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver GT30L32S4Wのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver GT30L32S4W用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver GT30L32S4Wドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver GT30L32S4Wプログラミング例が含まれています。

/ docディレクトリには、LibDriver GT30L32S4Wオフラインドキュメントが含まれています。

/ datasheetディレクトリには、GT30L32S4Wデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_gt30l32s4w_basic.h"

uint8_t res;
uint8_t buf[128];
uint8_t len;
uint16_t ch = 'A';

/* basic init */
res = gt30l32s4w_basic_init();
if (res != 0)
{
    return 1;
}

...

/* read 32 */
res = gt30l32s4w_basic_read_32(ch, buf, &len);
if (res != 0)
{
    /* basic deinit */
    (void)gt30l32s4w_basic_deinit();

    return 1;
}

...
    
/* print */
if (len == 64)
{
    (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_16X32_ASCII, buf, 64);
}
else
{
    (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_32X32_GB2312, buf, 128);
}

...
    
/* basic deinit */
(void)gt30l32s4w_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/gt30l32s4w/index.html](https://www.libdriver.com/docs/gt30l32s4w/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。