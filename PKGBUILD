pkgname=devbox
pkgver=0.1
pkgrel=1
pkgdesc="DevBox CLI tool for per-language dev environments"
arch=('x86_64')
url="https://github.com/Junaid433/DevBox"
license=('MIT')
depends=()
makedepends=('gcc' 'cmake' 'make')
source=("https://github.com/Junaid433/DevBox/archive/refs/tags/v${pkgver}.tar.gz")
sha256sums=('SKIP')

build() {
  cd "DevBox-${pkgver}"
  mkdir -p build
  cd build
  cmake ..
  make
}

package() {
  cd "DevBox-${pkgver}/build"
  install -Dm755 devbox "$pkgdir/usr/bin/devbox"
}
