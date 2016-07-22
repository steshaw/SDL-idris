module Main

import Graphics.SDL2 as SDL2
import System

main : IO ()
main = (do
  renderer <- SDL2.init 640 480
  loop renderer)
    where
      loop : SDL2.Renderer -> IO ()
      loop renderer = do
        SDL2.filledRect renderer 100 100 50 50 255 0 0 128
        SDL2.flipBuffers renderer
        event <- SDL2.pollEvent
        case event of
          Just (KeyDown KeyEscape) => pure ()
          Just (AppQuit) => pure ()
          _ => loop renderer
{-
  rest renderer)
    where
      rest : SDL2.Renderer -> IO ()
      rest renderer = do
        SDL2.filledRect renderer 100 100 50 50 255 0 0 128
        SDL2.flipBuffers renderer
        event <- SDL2.pollEvent
        case event of
          Just (KeyDown KeyEscape) => pure ()
          Just (AppQuit) => pure ()
          _ => rest renderer
-}
