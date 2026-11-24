# Backend Notes (from frontend work)

Places where the backend doesn't fully support the menus yet. Each one is
also marked with a `BACKEND NOTE:` comment in `main.cpp`.

1. **Selecting a flight by number** – The sample run uses "Enter the flight number: 1",
   but `Airline` only has `findFlight(code)`. The menu currently asks for the flight code.
   Suggested: add `getFlightCount()` and `getFlight(int index)` to `Airline`.
2. **`Airline::displayFlights()`** – Doesn't number the flights or show rows / seats per row
   like the sample run (`1. AC210 Calgary Vancouver 8 4`).
3. **`Flight::displaySeatMap()`** – Missing the `A B C D` column-letter header.
4. **`Passenger::print()`** – Fields are separated by single spaces, so rows don't line up
   under the passenger table headers. Use `setw` for aligned columns.
5. **`Flight::addPassenger()`** – No checks, returns `void`. The menu checks seat range,
   taken seats and duplicate IDs itself. Duplicate IDs are only checked within the selected
   flight because `Airline` can't search all flights' passengers.
6. **`Flight::removePassenger()`** – Returns `void`, so the menu has to look the passenger up
   first to know whether they exist. Returning a `bool` would be simpler.
