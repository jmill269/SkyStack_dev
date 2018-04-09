CC = g++

LIB_DIRS = -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dpm -lopencv_face -lopencv_photo -lopencv_freetype -lopencv_fuzzy -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core

INC_DIR =-I/usr/local/include/opencv -I/usr/local/include

ALL=cal_faster

all: $(ALL)

calibrate: calibrate.o
	@$(CC) $(LIB_DIRS) $(INC_DIR) ./calibrate.o -o ./calibrate
calibrate.o:
	@echo "Building 'calibrate'..."
	@$(CC) $(LIB_DIRS) $(INC_DIR) -c ./calibrate.cpp -o ./calibrate.o
cal_faster: cal_faster.o
	@$(CC) $(LIB_DIRS) $(INC_DIR) ./cal_faster.o -o ./cal_faster
cal_faster.o:
	@echo "Building 'cal_faster'..."
	@$(CC) $(LIB_DIRS) $(INC_DIR) -c ./cal_faster.cpp -o ./cal_faster.o


.PHONY: clean
clean:
	@echo "Removing generated files..."
	@rm -rf calibrate *.o *~ *#
