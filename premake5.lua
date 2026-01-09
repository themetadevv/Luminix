workspace "Base"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "sandbox"

include "projects/core"
include "projects/lxgl"
include "projects/luminix"
include "projects/sandbox"