all: ndk debug install

ndk:
	ndk-build

debug:
	ant debug

.PHONY: install
install:
	adb install -r bin/*-debug.apk

.PHONY: clean
clean:
	rm -r bin libs obj gen
