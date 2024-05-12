include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
)

set(FETCHCONTENT_QUIET OFF)
set(BUILD_SHARED_LIBS TRUE)

FetchContent_MakeAvailable(fmt)
