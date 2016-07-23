module Main

import Graphics.SDL2 as SDL2
import System

fail : (msg: String) -> IO ()
fail msg = do
  err <- getError
  fPutStr stderr $ msg ++ " failed:" ++ err
  fflush stderr
  System.exit 1

main : IO ()
main = (do
  renderer <- SDL2.init 640 480
  loop renderer)
    where
      loop : SDL2.Renderer -> IO ()
      loop renderer = do
        False <- SDL2.pollEventsForQuit | pure () -- Hacky check for quit events.
        True <- SDL2.setRendererDrawColor renderer 0 0 111 255
          | fail "setRendererDrawColor"
        SDL2.renderClear renderer
        SDL2.filledRect renderer 100 100 50 50 255 0 0 128
        SDL2.renderPresent renderer
{-
        event <- SDL2.pollEvent
        case event of
          Just (KeyDown KeyEscape) => pure ()
          Just (AppQuit) => pure ()
          _ => loop renderer
-}
        loop renderer
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
