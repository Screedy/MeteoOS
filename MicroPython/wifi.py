import network
import time
import socket

from config.config import Colors, Display


debug = False


# TODO: Needs to be completed and tested.


def web_page(list_of_networks):
    html = f"""
            <!DOCTYPE html>
            <html>
            <body>
            # Create form to input ssid from list of nearby networks and password and submit button
            <form action="/action_page.php">
                <label for="ssid">SSID:</label><br>
                <select name="ssid" id="ssid">
                    <?php
                        $networks = {list_of_networks};
                        foreach ($networks as $network) {{
                            echo "<option value=$network>$network</option>";
                        }}
                    ?>
                </select><br>
                <label for="password">Password:</label><br>
                <input type="text" id="password" name="password"><br><br>
                <input type="submit" value="Submit">
            </form>
            </body>
            </html>
            """
    return html


def ap_mode(ssid, password):
    """Creates an access point with the given ssid and password.

    :param ssid: The ssid of the access point.
    :param password: The password of the access point.
    :return: None
    """

    ap = network.WLAN(network.AP_IF)
    ap.config(essid=ssid, password=password)
    ap.active(True)

    while not ap.active():
        pass

    if debug:
        print("Activating AP mode...")
        print(f"SSID: {ssid}")
        print(f"IP Address To Connect to: {ap.ifconfig()[0]}")

    # Create a socket object and bind it to port 80
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('', 80))
    s.listen(5)

    while True:
        conn, addr = s.accept()
        print(f"Received a connection from {str(addr)}")
        request = conn.recv(1024)
        print(f"Content = {str(request)}")
        response = web_page(scan_networks())
        conn.send(response)
        conn.close()

        print(f"All networks: {scan_networks()}")


def scan_networks():
    """Scans for nearby networks and returns a list of them.

    :return: A list of nearby networks.
    """

    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    networks_raw = wlan.scan()
    networks = []

    for network_raw in networks_raw:
        networks.append(network_raw[0])

    return networks


if __name__ == "__main__":
    debug = True
    print("Testing WiFi...")
    ap_mode('Pico_test', 'PASSWORD')
