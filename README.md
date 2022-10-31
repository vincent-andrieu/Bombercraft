# Bombercraft
Bomberman with minecraft style - Epitech 2nd Year Project

* C++ multiplatform application (Mac, Windows, Linux).
* Local multiplayer
* Procedurally generated maps
* AI character

# Usage
## Docker
### Linux
- `docker build -f Dockerfile-linux -t bombercraft-linux .`
- `docker run --rm --name bombercraft-linux bombercraft-linux`
- `docker cp bombercraft-linux:/app/bomberman bombercraft-linux`
- `./bombercraft-linux`
### Mac
- `docker build -f Dockerfile-mac -t bombercraft-mac .`
- `docker run --rm --name bombercraft-mac bombercraft-mac`
- `docker cp bombercraft-mac:/app/bomberman bombercraft-mac`
- `./bombercraft-mac`

## Linux
   `mkdir build && cd build && cmake .. && make && cd .. && ./bomberman`

## Windows
`cmake .. && cmake --build && ./bomberman.exe`

# Trailer

[Trailer](https://www.youtube.com/watch?v=nsOyamoZKTI)

![01](github/img/01.png)

![02](github/img/02.png)

![03](github/img/03.png)

![04](github/img/04.png)

![05](github/img/05.png)
