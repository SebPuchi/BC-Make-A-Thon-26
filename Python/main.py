import serial
import serial.tools.list_ports
import time
import sys
import tty
import termios

def getch():
    """Reads a single character from the terminal without needing Enter."""
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def find_arduino_port():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        dev = port.device
        # Ignore Bluetooth and internal AirPod ports
        if "Bluetooth" in dev or "Incoming-Port" in dev or "Wireless" in dev:
            continue
        # Look for typical Arduino/USB labels
        if "usb" in dev.lower() or "usbmodem" in dev.lower() or "usbserial" in dev.lower():
            return dev
    return None

# --- Connection Setup ---
port_name = find_arduino_port()

if not port_name:
    print("No USB Arduino found")
    # List available ports to help debugging
    print("Available ports were:", [p.device for p in serial.tools.list_ports.comports()])
    exit()

try:
    # IMPORTANT: Ensure 9600 matches your Arduino's Serial.begin(9600)
    arduino = serial.Serial(port_name, 9600, timeout=0.1)
    time.sleep(2) # Wait for Arduino to reset after connection
    print(f"✅ Connected to {port_name}")
except Exception as e:
    print(f"❌ Connection error: {e}")
    exit()

print("--- CONTROLS ---")
print("W : Forward | S : Backward | Q : Quit")
print("(Use Capital W/S or Arrow Keys)")

try:
    while True:
        char = getch()
        
        # Quit condition
        if char.lower() == 'q':
            print("Exiting...")
            break
        
        # Handle W / S
        if char.lower() == 'w':
            arduino.write(b'F')
            print("Sent: F (Forward)")
        elif char.lower() == 's':
            arduino.write(b'B')
            print("Sent: B (Backward)")
            # Handle Spacebar for Servo
        elif char == ' ':
            arduino.write(b'X')
            print("Spacebar Pressed: Toggling Servo...")
            
        # Handle Arrow Keys (Esc + [ + A/B)
        elif char == '\x1b': 
            next1 = getch()
            if next1 == '[':
                direction = getch()
                if direction == 'A': # Up
                    arduino.write(b'F')
                    print("Sent: F (Arrow Up)")
                elif direction == 'B': # Down
                    arduino.write(b'B')
                    print("Sent: B (Arrow Down)")

except KeyboardInterrupt:
    print("\nInterrupted by user.")
finally:
    if 'arduino' in locals():
        arduino.close()
    print("Serial connection closed.")
