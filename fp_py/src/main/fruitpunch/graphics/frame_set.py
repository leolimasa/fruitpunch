from fruitpunch.native.elements.playable import Playable

class FrameSet(Playable):
    
    def __init__(self):
        super(FrameSet, self).__init__()
        
        self.frame_map = []
        self.name = ""
        self.original_frame_str = ""
    
    def render_single(self, frame_number):
        self.parent.render_single(self.frame_map[frame_number])
        
    def load_frames(self, frame_str):
        
        self.original_frame_str = frame_str
        self.frame_map = []
        ranges = frame_str.split(",")
        
        for range in ranges:
            
            numbers = range.split("-");
            start = int(numbers[0])
            stop = int(numbers[-1])
        
            while start <= stop:
                self.frame_map += [int(start)]
                start += 1
    
    def get_frames(self):
        return self.original_frame_str
    
    def calculate_duration(self):
        return len(self.frame_map)
    
    frames = property(get_frames, load_frames)