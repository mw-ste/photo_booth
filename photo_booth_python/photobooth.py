from gpiozero import LED as output_pin
from time import sleep
from datetime import datetime as dt


pin_number_remote_focus   = 23 # GPIO
pin_number_remote_capture = 24 # GPIO


class PhotoBooth:
    output_pin_focus   = None
    output_pin_capture = None

    def __init__(self):
        self.output_pin_focus   = output_pin(pin_number_remote_focus)
        self.output_pin_capture = output_pin(pin_number_remote_capture)

        self.output_pin_focus.on()
        self.output_pin_capture.on()


    def create_timestamp():
        return dt.strftime(dt.now(), "%Y%m%d%H%M%S")


    def capture_remote(self, wait_time_seconds = 3):
        self.output_pin_capture.off()
        sleep(wait_time_seconds)
        self.output_pin_capture.on()


    def capture_remote_and_download(self):
        pass


    def capture_gphoto(self):
        pass


    def capture_gphoto_and_download(self):
        pass

