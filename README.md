# Upgrade-Assmann-STAND.MOVE-M2.0
Arduino Projekt zum Upgrade der Steuerung "[Assmann STAND.MOVE M2.0 ohne Speicherfunktion](https://www.assmann.de/fileadmin/Downloads/Anleitungen/Easy-STS_BI_05-2021_DE-GB_ES.pdf)". Ergänzt werden zwei Tasten um den Tisch automatisiert auf zwei Höhen (bspw. Sitzen und Stehen) zu fahren. Der Tisch wird dabei mit zwei Relais gesteuert und die Höhe mit einem Abstandssensor gemessen. Ein OLED-Display zeigt die aktuelle Höhe ein. Die vorhandenen Tasten sollen weiterhin genutzt werden.

## Komponenten
* Arduino Nano
* Abstandssensor HC-SR02
* I2C OLED-Display 32 x 128 px
* 2x Relais SRD-5VDC-SL-C
* 2 Taster
* RJ45-Buchse
