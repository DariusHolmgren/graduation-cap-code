typedef struct {
	int start;		// start pixel
	int end;		// end pixel
} substrip;


substrip makeSubstrip(int start, int end) {
	substrip sub;
	sub.start = start;
	sub.end = end;
	return sub;
}

void setSubstrip(Adafruit_NeoPixel *pixels, substrip sub, int r, int g, int b) {
	for(int i = sub.start; i < sub.end; i++) {
		pixels->setPixelColor(i, pixels->Color(r, g, b));
	}
}

/* void clearSubstrip(Adafruit_NeoPixel pixels, substrip sub) {
	for(int i = sub.start; i < sub.end; i++) {
		pixels.setPixelColor(i, pixels.Color(0, 0, 0));
	}
} */
