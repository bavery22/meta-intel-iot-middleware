SUMMARY = "Library that creates Bluetooth GATT bindings using BlueZ over DBus"
SECTION = "libs"
AUTHOR = "Petre Efitme, Andrei Vasiliu"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=9d31ea1a7d987c590df4bce2dcdb25c0"

S = "${WORKDIR}/git"

inherit distutils-base pkgconfig cmake

PARALLEL_MAKE = "-j 1"

PACKAGES =+ "${PN}-java"

# tinyb-java package containing Java bindings
FILES_${PN}-java = "${libdir}/libjavatinyb.so* \
                    ${libdir}/java/ \
                    ${prefix}/src/debug/${BPN}/${PV}-${PR}/git/java/ \
                    ${libdir}/.debug/libjavatinyb.so* \
                    ${datadir}/tinyb/examples/java \
                   "
RDEPENDS_${PN}-java += "java-runtime"
INSANE_SKIP_${PN}-java = "dev-so debug-files"

PACKAGECONFIG ??= "java"
PACKAGECONFIG[java] = "-DBUILDJAVA=ON, -DBUILDJAVA=OFF, icedtea7-native openjdk-8,"

FILES_${PN}-doc = "${datadir}/tinyb/examples/*.cpp"

export JAVA_HOME="${STAGING_DIR}/${BUILD_SYS}/usr/lib/jvm/icedtea7-native"
export JAVA_HOME_target="${STAGING_LIBDIR}/jvm/java-8-openjdk"

cmake_do_generate_toolchain_file_append() {
  echo "
set (JAVA_AWT_INCLUDE_PATH ${JAVA_HOME_target}/include CACHE PATH \"AWT include path\" FORCE)
set (JAVA_AWT_LIBRARY ${JAVA_HOME_target}/jre/lib/i386/libjawt.so CACHE FILEPATH \"AWT Library\" FORCE)
set (JAVA_INCLUDE_PATH ${JAVA_HOME_target}/include CACHE PATH \"java include path\" FORCE)
set (JAVA_INCLUDE_PATH2 ${JAVA_HOME_target}/include/linux CACHE PATH \"java include path\" FORCE)
set (JAVA_JVM_LIBRARY ${JAVA_HOME_target}/jre/lib/i386/libjvm.so CACHE FILEPATH \"path to JVM\" FORCE)
" >> ${WORKDIR}/toolchain.cmake
}

DEPENDS_${PN} = "cmake (>= 3.1) glib-2.0 glib-2.0-native"
RDEPENDS_${PN} = "bluez5 (>= 5.37)"

