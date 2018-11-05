# Pebble-RedBlueRed

A port of
[Red Blue Red!](https://play.google.com/store/apps/details?id=com.javierrizzo.redbluered)
for Pebble Smartwatch.

## Compatibility

| Device            | Status                                                                             |
| ----------------- | ---------------------------------------------------------------------------------- |
| Pebble            | Works, but *sometimes* crashes on the Game Over window.                            |
| Pebble Steel      | Untested. Sould work the same as the original Pebble.                              |
| Pebble Time       | Works.                                                                             |
| Pebble Time Steel | Untested, but it *should* work, as it does on the PT.                              |
| Pebble Time Round | Always crashes on the Game Over window. Content is not adapted for the PTR screen. |
| Pebble 2 HR+      | Works.                                                                             |
| Pebble 2 SE       | Untested, but it *should* work, as it does on the 2 HR+                            |

## Installing

[Download the .pbw file](https://github.com/JavierRizzoA/Pebble-RedBlueRed/releases)
in your phone and open it with the Pebble App.

I'll upload it to the Rebble Appstore as soon as there's a way to do so.

## Building & Installing from Source

```
pebble build

pebble install --phone [PHONE_IP_ADDRESS]
```

## License

Copyright 2018 Javier Rizzo-Aguirre

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see http://www.gnu.org/licenses/.
