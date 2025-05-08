#1. Opis zadania:#

  Projekt to implementacja Bota UDP wysyłającego cyklicznie symulowane dane termometru cyfrowego do serwera z użyciem języka C.

#2. Analiza i podejście:#

  Zadanie rozpocząłem od analizy wymagań, doboru odpowiednich narzędzi i bibliotek oraz od poszerzenia wiedzy z zakresu programowania sieciowego w języku C, konkretnie gniazd sieciowych oraz działania protokołu UDP.

#3. Działanie aplikacji:#

Aplikacja przyjmuje parametry z linii komend: adres IPv4 serwera, port UDP serwera oraz interwał czasowy mierzony w sekundach. W każdej iteracji generowany jest jest pakiet danych, który zaimplementowany jest jako struktura:
- znacznik czasowy (uint32_t)
- temperatura (uint16_t)
- status zasilania (uint8_t - 0:sieciowe, 1: bateryjne)
- identyfikator pomiaru (uint8_t)
- suma kontrolna (uint8_t suma wszystkich poprzednich bajtów % 256, aby zajmowała 1 bajt)
  
Pakiety wysyłane są za pomocą UDP. Każdy pakiet logowany jest na ekran konsoli w postaci czytelnej dla użytkownika. Ze względu na wymaganie minimalizacji struktury, oraz na to, że w strukturze nie mogły znajdować się liczby zmiennoprzecinkowe, czas przechowywany jest w standardowym formacie UNIXOWYM, a temperatura w postaci liczby całkowitej). Przez co konieczne jest poprawne formatowanie danych wyświetlanych na ekranie konsoli, lub docelowo na serwerze.

#4. Testowanie:#

Aplikację przetestowałem lokalnie tworząc prosty serwer UDP w C, który dekodował przychodzące dane i wyświetlał je na konsoli w czytelnej formie. Upewniłem się również, że aplikacja nie pozwoli nam podać niepoprawnych danych testowych na wejściu.

#5. Moje wątpliwości podczas realizacji zadania:#

Jedną z moich wątpliwości był sposób reprezentacji statusu zasilania. Na początku rozważałem enum, aby móc od razu przesyłać czytelne dla użytkownika dane, lecz spowodowałoby to niepotrzebne zwiększenie rozmiaru struktury, co byłoby sprzeczne z wymaganiami. Ostatecznie postawiłem na coś, co również wydawało się naturalne, czyli reprezentowanie stanu zasilania za pomocą 0 lub 1. Stawia to jednak konieczność wspólnej umowy na to, która cyfra odpowiada któremu stanowi.
Moją drugą wątpliwością było, co zrobić w przypadku tzw. 'uint8 overflow' w identyfikatorze pomiaru. Zdecydowałem się na resetowanie jego stanu w momencie przekroczenia maksymalnego zakresu tego formatu. Zrobiłem tak z myślą o zapewnieniu ciągłości przesyłania danych. 
