#useage:
#include($$PWD/xxx.pri)

include(D:\Code\Go\src\github.com\pjh130\qt\Core\email\email.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\log_v1\log_v1.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\network_v1\network_v1.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\ThreadHandle\threadhandle.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\excel\excel.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\qzip\qzip.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\qtsql\qtsql.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\file\file.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\time\time.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\image\image.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\string\string.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\os\os.pri)
include(D:\Code\Go\src\github.com\pjh130\qt\Core\textcodec\textcodec.pri)

#加入路径
CORE_LIBRARY_LOCATION = $$PWD
INCLUDEPATH += $$CORE_LIBRARY_LOCATION
DEPENDPATH += $$CORE_LIBRARY_LOCATION


