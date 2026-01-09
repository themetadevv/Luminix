workspace "Base"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "sandbox"

include "projects/luminix"
include "projects/sandbox"