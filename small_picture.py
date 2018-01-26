from PIL import Image, ImageTk
im = Image.open('../photos/init.jpg')
out = im.resize((400, 300),Image.ANTIALIAS)

out.save('../photos/init_small.jpeg', 'jpeg')
