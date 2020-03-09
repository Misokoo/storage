sudo su
cd /home/
mkdir joe
cd joe
mkdir image d1 d2 
touch f2 f3 
cd d1
touch rapport_stage.doc f1
cd ..
cd d2
mkdir d21
cd d21
touch f21
cd /home/joe/image/
touch DSC03456.jpg DSC03457.jpg DSC05301.jpg DSC05302.jpg
cd /home/joe/d1/
cd ..
cd /home/joe
cp d1/rapport_stage.doc d2/d21/echo 
cp /home/joe/image/DSC03* /home/joe/d1
cd /home/joe/d1
mv DSC03456.jpg image_chat.jpg
mv DSC03457.jpg /home/joe/d2/image_chien.jpg
rm /home/joe/image/*
rmdir /home/joe/image









