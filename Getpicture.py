import cv2

cap = cv2.VideoCapture(0)
# cap.set(3,960)
# cap.set(4,540)
while(1):
    ret, frame = cap.read()
    cv2.imshow("please input your photo", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.imwrite("../photos/init.jpg", frame)
        break
cap.release()
cv2.destroyAllWindows()
