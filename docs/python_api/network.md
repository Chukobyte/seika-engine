# roll.network

## Network

Interface for network related operations for multiplayer.

### Variables

None.

---

### Signals

**[Server](#server) and [Client](#client) signals.**

```python
peer_connected
```

Emitted once a peer is connected to the [Server](#server).

```python
peer_disconnected
```

Emitted once a peer is disconnected from the [Server](#server).

```python
message_received
```

Emitted once a message is received from the network.

**[Client](#client) only signals.**

```python
connected_to_server
```

Emitted once a client successfully connects to a [Server](#server).

```python
connection_to_server_failed
```

Emitted once a client fails to connect to a [Server](#server).

---

### Methods

```python
connect_signal(signal_id: str, listener_node: roll.node.Node, function_name: str) -> None:
```

Connects to network related signal.

---

## Server

Interface for server related operations for multiplayer.

### Variables

None.

---

### Signals

None.

---

### Methods

```python
start(port: int) -> None:
```

Starts server on designated `port`.

```python
stop() -> None:
```

Stops previously started server.

```python
send_message_to_all_clients(message: str) -> None:
```

Sends message to all connected clients.

---

## Client

Interface for client related operations for multiplayer.

### Variables

None.

---

### Signals

None.

---

### Methods

```python
connect(endpoint: str, port: int) -> None:
```

Connects to a server with the passed in `endpoint` and `port`.

```python
disconnect() -> None:
```

Disconnects from a server.

```python
send_message_to_server(message:str) -> None:
```

Sends message to the server.

---
