# 🚦 Sygnalizacja świetlna na skrzyżowaniu – Arduino

Prosty projekt sygnalizacji świetlnej dla skrzyżowania czterech dróg (lewa, prawa, górna, dolna), zrealizowany na Arduino. Każdy kierunek ma własny czujnik oraz parę diod (czerwona i zielona). Program gwarantuje, że **w danej chwili zielone światło może mieć tylko jeden kierunek**.

## ✨ Funkcje

- Obsługa 4 kierunków ruchu: lewy, prawy, górny, dolny
- Zielone światło włącza się dopiero po wykryciu pojazdu przez czujnik
- Blokada konfliktów – dwa zielone światła naraz są niemożliwe
- Zielone światło pozostaje włączone **5 sekund po przejechaniu ostatniego pojazdu**
- Domyślny stan skrzyżowania: wszystkie światła czerwone
- Opóźnienie liczone za pomocą `millis()`

## 🧰 Wymagane elementy

| Element | Ilość |
|---|---|
| Arduino (np. Uno) | 1 |
| Dioda LED czerwona | 4 |
| Dioda LED zielona | 4 |
| Rezystor ok. 220 Ω (do diod) | 8 |
| Czujnik ruchu / obecności (lub przycisk do symulacji) | 4 |
| Rezystor 10 kΩ (pull-down dla wejść) | 4 |
| Płytka stykowa i przewody | – |

## 🔌 Schemat połączeń

| Kierunek | Czujnik (wejście) | Dioda czerwona | Dioda zielona |
|---|---|---|---|
| Lewy (`LEFT`) | 12 | 8 | 9 |
| Prawy (`RIGHT`) | 11 | 4 | 5 |
| Górny (`TOP`) | 13 | 2 | 3 |
| Dolny (`BOTTOM`) | 10 | 7 | 6 |

> ⚠️ Piny czujników (10–13) są skonfigurowane jako zwykłe `INPUT`. Wejście musi być zawsze wyraźnie podciągnięte do stanu niskiego (rezystor pull-down lub czujnik aktywnie ustawiający LOW). W przeciwnym razie pin może „pływać” i losowo odczytywać stan wysoki, co powoduje fałszywe zapalanie zielonego światła.

## ⚙️ Jak to działa

1. Po uruchomieniu funkcja `allRed()` zapala wszystkie czerwone diody.
2. W pętli `loop()` program kolejno sprawdza kierunki: lewy → prawy → górny → dolny.
3. Gdy czujnik danego kierunku odczyta stan `HIGH`, program wyłącza czerwone i włącza zielone światło.
4. Dopóki czujnik wykrywa pojazdy, zielone światło pozostaje włączone, a licznik czasu jest odświeżany.
5. Po tym, jak czujnik przejdzie w stan `LOW`, zielone światło świeci jeszcze **5 sekund**, a następnie wraca czerwone.
6. Dopiero wtedy program przechodzi do sprawdzenia kolejnego kierunku.

Fragment logiki pojedynczego kierunku:

```cpp
void detectLeft() {
  unsigned long start = millis();
  bool wasGreen = false;

  while (digitalRead(12) == HIGH) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    start = millis();
    wasGreen = true;
  }
  if (wasGreen) {
    while (millis() - start < 5000) { }
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
}
```

Zmienna `wasGreen` zapewnia, że 5-sekundowe oczekiwanie odbywa się tylko wtedy, gdy zielone światło faktycznie zostało włączone. Bez niej każdy kierunek bez pojazdów blokowałby program na 5 sekund.

## 🚀 Uruchomienie

1. Zepnij układ zgodnie z tabelą połączeń.
2. Otwórz plik z kodem w Arduino IDE (lub wklej go do symulatora, np. Tinkercad).
3. Wybierz właściwą płytkę i port.
4. Wgraj program i przetestuj działanie czujników.

## ⚠️ Ograniczenia

- **Program jest blokujący.** Gdy jeden kierunek ma zielone światło, pozostałe czujniki nie są odczytywane. Pojazdy oczekujące na innych kierunkach zostaną obsłużone dopiero po zakończeniu bieżącego cyklu.
- **Kolejność obsługi jest stała** (lewy → prawy → górny → dolny), więc nie ma rotacyjnego priorytetu.
- **Pojazd, który nadjedzie podczas 5-sekundowego oczekiwania, nie wydłuża go.** Pętla oczekiwania nie odczytuje czujnika. Aby licznik był odnawiany także w tym czasie, dodaj w pętli sprawdzenie czujnika:

  ```cpp
  while (millis() - start < 5000) {
    if (digitalRead(12) == HIGH) {
      start = millis();
    }
  }
  ```
- Brak dedykowanej fazy „wszystko czerwone” między zmianą kierunków.

## 💡 Pomysły na rozwój

- Wersja nieblokująca, w której wszystkie czujniki są odczytywane przez cały czas (np. maszyna stanów z jedną zmienną `owner`)
- Rotacyjny priorytet kierunków dla większej sprawiedliwości
- Faza żółta oraz krótki czas „wszystko czerwone” między kierunkami
- Programowa eliminacja drgań (debounce) czujników

## 📄 Licencja

Projekt udostępniony na licencji MIT. Możesz go dowolnie używać, modyfikować i rozwijać.
