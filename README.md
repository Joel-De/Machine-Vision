Place the 'FILTERS' Folder in the following directory, "C:\FILTER"

The application uses 2 kernels to detect the location of a hand in a dark glove within a given frame. A webcam is required, the application will attempt to use the default one and output an error if it cannot find one.

The application uses a simple technique, where it calculates the convolution of the positive kernel and the source image, then subtracts it from the a weighted convolution of the negative kernel. This gives values a normalized value, and taking the maximum of it returns the location of the object. Currently the program has no restriction, so it will always return the object that closest resembles a hand, but this can be modified to threshold the value.

![Hand](https://user-images.githubusercontent.com/71618484/99600369-4bb22c80-29cb-11eb-96fb-454adc1ae543.gif)
