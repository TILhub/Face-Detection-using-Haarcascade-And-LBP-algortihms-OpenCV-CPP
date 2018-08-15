### Face Detection Using Haarcascade And LBP algortihms OpenCV
A computer program that decides whether an image is a positive image (face image) or negative image (non-face image) is called a classifier. A classifier is trained on hundreds of thousands of face and non-face images to learn how to classify a new image correctly. OpenCV provides us with two pre-trained and ready to be used for face detection classifiers:

    Haar Classifier
    LBP Classifier

Both of these classifiers process images in gray scales, basically because we don't need color information to decide if a picture has a face or not (we'll talk more about this later on). As these are pre-trained in OpenCV, their learned knowledge files also come bundled with OpenCV opencv/data/.

To run a classifier, we need to load the knowledge files first, as if it had no knowledge, just like a newly born baby (stupid babies).

Each file starts with the name of the classifier it belongs to. For example, a Haar cascade classifier starts off as haarcascade_frontalface_alt.xml.
