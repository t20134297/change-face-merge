python Getpicture.py
inf=`python3 face_detect.py`
python3 show_input_photo.py $inf  &
python3 show_original_photo.py $inf &
