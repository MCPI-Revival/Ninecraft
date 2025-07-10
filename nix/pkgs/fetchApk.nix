{
  fetchzip,
  lib,
}: {
  url,
  hash ? lib.fakeHash,
}:
fetchzip {
  inherit url hash;
  extension = "zip";
  stripRoot = false;
}
