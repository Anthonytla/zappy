This is Zappy, a automated game with four player and a server. The game starts once all the four players are connected.
The IA follow these rules, it can:
- Turn 90° to the left (left).
- Turn 90° to the right (right).
- Move forward one square if possible (fwd).
- Turn 90° to the left and then move forward one square if possible (leftfwd).
- Turn 90° to the right and then move forward one square if possible (rightfwd).
Resources:
- Stones have different effects when collected:
    - Linemate (yellow gem) increases the current player's life points by 1.
    - Deraumere (blue stone) decreases the current player's life points by 1.
    - Sibur (green gem) decreases the life of all other players by 1.
    - Mendiane (red gem) increases the current player's victory points by 1.

Install the dependencies by executing 
```bash
chmod +x install.sh
./install.sh
```
Command to launch the server from the 'server' folder:
```bash
make
server  <port number>
```

Default values:


Command to launch the client from the 'client' folder:
```bash
make
client <port number>
```
Default values:

