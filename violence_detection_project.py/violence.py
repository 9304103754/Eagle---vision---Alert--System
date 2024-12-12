import cv2
import numpy as np
from tensorflow.keras.models import load_model
import urllib.request

# Load the pre-trained model
model = load_model('C:/Users/Ravi Kumar Jha/Downloads/violence_detection_model (1).h5')  # Replace with your model's path

def preprocess_frame(frame):
    """
    Preprocess the frame for the model.
    Resize, normalize, and add batch dimension.
    """
    resized_frame = cv2.resize(frame, (224, 224))  # Adjust size to your model's input
    normalized_frame = resized_frame / 255.0      # Normalize pixel values
    return np.expand_dims(normalized_frame, axis=0)

def is_violence(prediction):
    """
    Analyze the model's prediction to determine violence.
    Returns True if violence is detected.
    """
    return prediction[0][0] > 0.7  # Adjust threshold as needed

def send_alert():
    """
    Send an alert when violence is detected.
    Currently prints a message to the console.
    Replace this function with SMS/Email integration if needed.
    """
    print("ALERT: Violence detected! Immediate action required.")

# Replace the URL with the IP camera's stream URL
url = 'http://192.168.219.110/cam-hi.jpg'

# Create a window for the live stream
cv2.namedWindow("Live Stream", cv2.WINDOW_AUTOSIZE)

while True:
    try:
        # Fetch a frame from the IP camera stream
        img_resp = urllib.request.urlopen(url)
        imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
        frame = cv2.imdecode(imgnp, -1)

        # Preprocess the frame and predict
        processed_frame = preprocess_frame(frame)
        prediction = model.predict(processed_frame)

        # Check for violence
        if is_violence(prediction):
            print("Violence detected!")
            
            # Optionally, save the frame where violence is detected
            image_path='violence_detected.jpg'
            cv2.imwrite(image_path, frame)
            send_alert()

        # Display the live stream
        cv2.imshow("Live Stream", frame)

        # Exit the loop when 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    except Exception as e:
        print(f"Error fetching or processing frame: {e}")
        break

# Clean up and close the window
cv2.destroyAllWindows()
