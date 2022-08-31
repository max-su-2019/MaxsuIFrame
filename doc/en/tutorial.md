# How To Apply Invincibility Frames for Animations
<br/> 

## How I-Frame Genrator Works:
---  
I-Frame Generator applies custom invincibility frames (refer as I-frame below) to game engine by hooking the hit damage delivering function as well as the magic damage delivering function. It would checks for the annotations of the current active animation clips of an actor, if the local time of a clip is bewteen an I-frame duration, it will then force the game engine to recognize the actor as invincibile.    

---
<br/> 

## How to generate I-Frame:  
--- 
<br/> 

### New Method (Recommended)    

Simply writing an annotations in your animation file like:

```
0.100000 SpecialFrames_Invincible{"Duration":0.5}
```

The float number `0.100000` in the leftmost represents the start time of this I-Frame, while the number `0.5` in the rightmost represents the duration of this I-Frame would lasting. Therefore, the anotation above would make the actor Invincible between 0.100000 to 0.600000 animation time.

All of those time above represents to the local time of the animation.  
Multiple IFrame annotations are supported to add into same animation file.  

<br/>  

### Old Method (Not recommended)  

The old method of generate I-Frame through behavior modification is still remains, however it is not recommend to achieve with this method.

To generate I-Frame through behaviour modification, you need to create two boolean varible "bIframeActive" and "bInIframe“ in the behaviour graph, then ensure both of them are true when the animation is in the invincibility frames, and ensure at least one of them is false when not in the I-frame.
I suggest that you can assign "bIframeActive" to the active modifiy of the state machine, while "bInIframe“ to define the I-frame duration.
You can check this [behaviour project](https://www.nexusmods.com/skyrimspecialedition/mods/56956?tab=files&file_id=234593) for reference.

--- 


