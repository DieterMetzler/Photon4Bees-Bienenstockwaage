# Photon4Bees - WLAN Stockwaage

Die Photon4Bees - WLAN Stockwaage basiert auf dem Photon von Particle.
Das Photon von Particle ist ein kleines Microcontrollerboard mit einem ARM Cortex M3 Microcontroller und einem WiFi Modul von Broadcom und eignet sich damit ideal für die Entwicklung von Internet of Thing (IoT) Projekten wie beispielsweise einer Stockwaage.

Die Beschreibung der Hardware findet ihr auf www.4bees.at

Dieses Repository dient der Entwicklung der Firmware für das Photon für eine Stockwaage mit folgenden Anforderungen:

    -> Herstellung der Internetverbindung über die SoftAP Funktion
    -> Verbindung mit dem Datenserver http://cloud.4bees.at herstellen - über den API Schlüssel des Datenkanals
    -> Kalibrierung der Waage und Speicherung des Scalefactors und des Offsets in den Feldern 7 und 8 des Datenkanals
    -> stündliche Messung von Gewicht, Aussentemperatur, Luftfeuchtigkeit aussen, Innentemperatur im Bienenvolk, Luftfeuchtigkeit im Bienenvolk und Ladezustand des Akkus
       (Feld 1 - Feld 6 des Datenkanals)
    -> Übermittlung der Daten an den Datenserver http://cloud.4bees.at

