module Graphics.SDL2

import Graphics.Config

%include C "sdlrun.h"
%link C    "sdlrun.o"

-- Set up a window

export
data Renderer = MkRenderer Ptr

export
data Surface = MkSurface Ptr

export
init : Int -> Int -> IO Renderer
init x y = do ptr <- do_startSDL
              return (MkRenderer ptr)
  where do_startSDL = foreign FFI_C "startSDL" (Int -> Int -> IO Ptr) x y

export
quit : IO ()
quit = foreign FFI_C "SDL_Quit" (IO ())

export
flipBuffers : Renderer -> IO ()
flipBuffers (MkRenderer ptr) 
     = foreign FFI_C "flipBuffers" (Ptr -> IO ()) ptr


-- Some drawing primitives

export
filledRect : Renderer -> Int -> Int -> Int -> Int ->
                           Int -> Int -> Int -> Int -> IO ()
filledRect (MkRenderer ptr) x y w h r g b a 
      = foreign FFI_C "filledRect"
           (Ptr -> Int -> Int -> Int -> Int ->
            Int -> Int -> Int -> Int -> IO ()) ptr x y w h r g b a

export
filledEllipse : Renderer -> Int -> Int -> Int -> Int ->
                              Int -> Int -> Int -> Int -> IO ()
filledEllipse (MkRenderer ptr) x y rx ry r g b a 
      = foreign FFI_C "filledEllipse"
           (Ptr -> Int -> Int -> Int -> Int ->
            Int -> Int -> Int -> Int -> IO ()) ptr x y rx ry r g b a

export
drawLine : Renderer -> Int -> Int -> Int -> Int ->
                         Int -> Int -> Int -> Int -> IO ()
drawLine (MkRenderer ptr) x y ex ey r g b a 
      = foreign FFI_C "drawLine"
           (Ptr -> Int -> Int -> Int -> Int ->
            Int -> Int -> Int -> Int -> IO ()) ptr x y ex ey r g b a

-- TODO: More keys still to add... careful to do the right mappings in
-- KEY in sdlrun.c

public export
data Key = KeyUpArrow
         | KeyDownArrow
         | KeyLeftArrow
         | KeyRightArrow
         | KeyEsc
         | KeySpace
         | KeyTab
         | KeyF1
         | KeyF2
         | KeyF3
         | KeyF4
         | KeyF5
         | KeyF6
         | KeyF7
         | KeyF8
         | KeyF9
         | KeyF10
         | KeyF11
         | KeyF12
         | KeyF13
         | KeyF14
         | KeyF15
         | KeyLShift
         | KeyRShift
         | KeyLCtrl
         | KeyRCtrl
         | KeyAny Char

Eq Key where
  KeyUpArrow    == KeyUpArrow     = True
  KeyDownArrow  == KeyDownArrow   = True
  KeyLeftArrow  == KeyLeftArrow   = True
  KeyRightArrow == KeyRightArrow  = True

  KeyEsc   == KeyEsc   = True
  KeyTab   == KeyTab   = True
  KeySpace == KeySpace = True

  KeyF1    == KeyF1    = True
  KeyF2    == KeyF2    = True
  KeyF3    == KeyF3    = True
  KeyF4    == KeyF4    = True
  KeyF5    == KeyF5    = True
  KeyF6    == KeyF6    = True
  KeyF7    == KeyF7    = True
  KeyF8    == KeyF8    = True
  KeyF9    == KeyF9    = True
  KeyF10   == KeyF10   = True
  KeyF11   == KeyF11   = True
  KeyF12   == KeyF12   = True
  KeyF13   == KeyF13   = True
  KeyF14   == KeyF14   = True
  KeyF15   == KeyF15   = True

  KeyLShift == KeyLShift = True
  KeyRShift == KeyRShift = True
  KeyLCtrl  == KeyLCtrl  = True
  KeyRCtrl  == KeyRCtrl  = True

  (KeyAny x)    == (KeyAny y)     = x == y
  _             == _              = False

public export
data Button = Left | Middle | Right | WheelUp | WheelDown

Eq Button where
  Left == Left = True
  Middle == Middle = True
  Right == Right = True
  WheelUp == WheelUp = True
  WheelDown == WheelDown = True
  _ == _ = False

public export
data Event = KeyDown Key
           | KeyUp Key
           | MouseMotion Int Int Int Int
           | MouseButtonDown Button Int Int
           | MouseButtonUp Button Int Int
           | Resize Int Int
           | AppQuit

Eq Event where
  (KeyDown x) == (KeyDown y) = x == y
  (KeyUp x)   == (KeyUp y)   = x == y
  AppQuit     == AppQuit     = True
  (MouseMotion x y rx ry) == (MouseMotion x' y' rx' ry')
      = x == x' && y == y' && rx == rx' && ry == ry'
  (MouseButtonDown b x y) == (MouseButtonDown b' x' y')
      = b == b' && x == x' && y == y'
  (MouseButtonUp b x y) == (MouseButtonUp b' x' y')
      = b == b' && x == x' && y == y'
  _           == _           = False

export
pollEvent : IO (Maybe Event)
pollEvent 
    = do MkRaw e <- 
            foreign FFI_C "pollEvent" (Ptr -> IO (Raw (Maybe Event))) prim__vm
         return e
