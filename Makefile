CC=clang
LIBS=-l portaudio

wavwrite: wavwrite.c
	$(CC) $< $(LIBS) -o $@

wavread: wavread.c wavhdr.c
	$(CC) $^ -o $@

clean:
	rm -rf wavwrite
	rm -rf wavread
	rm -rf output.wav

help:
	echo "Possible targets:"
	echo "    wavwrite"
	echo "    wavread"
	echo "    clean"
