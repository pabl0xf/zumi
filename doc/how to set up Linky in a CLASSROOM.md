1. Insert the microSD card into your computer.

2. When the "Linky" drive appears, navigate to the **/boot** folder.

3. Create a file in this directory called wpa_supplicant.conf. Open the file and paste the following text:

    >network={<br>
    		  ssid="YOUR_NETWORK_NAME"<br>
    		  psk="YOUR_PASSWORD"<br>
    		  key_mgmt=WPA-PSK<br>
      }

      Replace YOUR_NETWORK_NAME with your WiFi network name and YOUR_PASSWORD with your WiFi pFssword. Keep the quotation marks. (The key_mgmt field specifies what kind of security the WiFi network uses.)

5. Move the SDCard to the Pi and connect the power port to a power supply via the USB cable.
[TODO] need photo 
Wait 2 minutes for the Pi to book, then unplug it again.

6. Insert the SD Card back into your computer, and find the file "this_is_the_ip.txt" in the **/boot** folder.

7. Take note of the IP address, and re-insert the SDCard into the Pi, and power it using the USB cable.

8. Test that Linky is connected to your WiFi by typing into the terminal. Replace the IP address for yours.  
    >ping <ip_address>
    
    If you see "Request timed out", then Linky is not connected. [TODO] link to a connection troubleshooting guide

## We're now going to connect to Linky so that you can use it's Desktop from your computer... 
7. Download and install VNC viewer

8. Open VNC Viewer and enter the following into the field for the VNC server address:

>linky.local

When prompted, the default password you will type in will be “pi”. Give the display a few seconds to load.