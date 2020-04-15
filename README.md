# DSA-Homework-1
Fakultet elektrotehnike Tuzla - Distribuirani sistemi automatizacije


Zadatak:

Potrebno je modifikovati jednostavnu client-server aplikaciju za prenos datoteka preko Interneta
(fileclient.c i fileserver.c) koja se nalazi na dropboxu materijala za predmet.

https://www.dropbox.com/sh/mbsvwbp456e6lav/AAAC8VcVgNcwZZCEnoq7ZoFPa?dl=

Client strana aplikacije prihvata ime datoteke iz komandne linije i prenosi je server strani aplikacije,
koja je prihvata i pod istim imenom upisuje na disk.

Client-side aplikacioni protokol:

1. Client uspostavlja konekciju sa Serverom
2. Client šalje Serveru string sa imenom datoteke terminiran sa '\n' (new line) karakterom
    ( npr. moja_datoteka.txt\n )
3. Nakon toga client šalje sadržaj datoteke u blokovima npr. od 512 bajta do kraja iste
4. Client zatvara konekciju i terminira program

Server-side aplikacioni protokol:

1. Server prihvata konekciju od clienta
2. Prihvata string sa imenom datoteke (čitajte string karakter po karakter do pojave \n
    karaktera koji signalizira kraj stringa)
3. Server otvara datoteku sa procitanim imenom i prihvata blokove datoteke (512 bajta) i
    upisuje ih u datoteku
4. Nakon transfera zatvara konekciju
5. Čeka na slijededi zahtjev

NAPOMENA: startajte server i client iz različitih foldera


