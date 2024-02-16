[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver GT30L32S4W
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/gt30l32s4w/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

GT30L32S4W ist ein Bibliothekschip für chinesische Schriftzeichen, der eine 12x12-Punktmatrix, eine 16x16-Punktmatrix, eine 24x24-Punktmatrix und eine 32x32-Punktmatrix umfasst. Es unterstützt chinesische GB2312-Standardzeichen (einschließlich gesetzlicher Genehmigung der National Information and Standardization Commission) und ASCII-Zeichen. Das Anordnungsformat ist horizontal. Benutzer können die in diesem Handbuch bereitgestellte Methode verwenden, um die Adresse der Zeichenmatrix im Chip anhand des internen Zeichencodes zu berechnen und die Zeichenmatrixinformationen kontinuierlich von dieser Adresse zu lesen.

LibDriver GT30L32S4W ist der von LibDriver eingeführte Vollfunktionstreiber von GT30L32S4W. Er bietet die Funktion des Punktmatrix-Lesens. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver GT30L32S4W-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver GT30L32S4W SPI.

/test enthält den Testcode des LibDriver GT30L32S4W-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver GT30L32S4W-Beispielcode.

/doc enthält das LibDriver GT30L32S4W-Offlinedokument.

/Datenblatt enthält GT30L32S4W-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/gt30l32s4w/index.html](https://www.libdriver.com/docs/gt30l32s4w/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.