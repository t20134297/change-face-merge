import cv2

cap = cv2.VideoCapture(0)
while(1):
    ret, frame = cap.read()
    cv2.imshow("capture", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.imwrite("../photos/fangjian2.jpg", frame)
        break
cap.release()
cv2.destroyAllWindows()
