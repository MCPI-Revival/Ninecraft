{
  lib,
  fetchApk,
  stdenv,
}: let
  versions = {
    a0_1_0 = {
      arm = "sha256-YVCtc8O6HU4ZFfe2mM83V9t0BHyMJ7LsDZjVpS7xVcI=";
      touch = "sha256-VrmTfTOoMTywFvCrOk9C5ei6XLLBS8zvoji3NvdJWKA=";
    };
    a0_1_1 = "sha256-l4N7PnZcgdYWYuBCLDbRIr+9ahxg6E8rzfeiVqpAQsM=";
    a0_1_1j = "sha256-ppeC63SWlPBjVaYHIcQtdrWXfmAARCYngY7uBTvW5aU=";
    a0_1_2 = "sha256-gRdxHs5RfIwCmySdGTSiayM7G/u/hrBPfpirgPfefRc=";
    a0_1_2j = "sha256-Hf1qpWOhdI9sQBcf61Y8cZG47RLMZLwpcdHxQKexJcM=";
    a0_1_3-1 = {
      arm = "sha256-GkK10so9wJ33rKIm4WDoM9XDNWVEv9mzI9n2Xpp7m2w=";
      demo = "sha256-uApiNw5BNWRwTnY+jnLNgx3tdRLznydLDlJw6jBe8HY=";
    };
    a0_1_3j = {
      arm = "sha256-9SgsMf3GpSOyiczz99Vggn07TYGQIUpOnPuhUfEWdqI=";
      demo = "sha256-tTVOVTIL+XVzhHQBH6J/f9A7r+56PBBFOHSHsgef1BA=";
    };
    a0_1_3-2 = {
      arm = "sha256-9SgsMf3GpSOyiczz99Vggn07TYGQIUpOnPuhUfEWdqI=";
      demo = "sha256-i06SUxFBMgpxuuoAFlIr1Vu9GFtdNSdU/eYxcW0w3Fw=";
    };
    a0_2_0-1 = "sha256-HVdVtP5aKICnbx33Hb1o8SiuGHXe9JIgm7FFEGvnefE=";
    a0_2_0-2 = "sha256-WmOu00Hq1sjjTcqfu6FIYNBTsn/75egfC2dPmqc8D2g=";
    a0_2_0j = "sha256-YviYMf0xVkP5g+jJu5AXdyNkQGSFVwzoVAUJZBSwEV4=";
    a0_2_1-1 = "sha256-z4gbLiA5edOpINJ9m3bLjJ6TYa0JP1/3HH5o+77doVI=";
    a0_2_1alpha2 = "sha256-II++9Xh0QbxNTwNcZ1x09WPD1ZVz57jxZZe5rrX/VR8=";
    a0_2_1-2 = "sha256-hoBw9dc2qDhcaY0iuEnG7EY49KoYPDkVddbamX0IfHk=";
    a0_2_1j = "sha256-dZAd80sv79Hs8TxVDPPbt64VAdUNe8Ag/9tJSX1h7ao=";
    a0_2_2 = "sha256-ZWhiXeJMhTsoNlQkNkxjBsky5eKPd/dQPuoLR0ZQ5aY=";
    a0_3_0-1 = "sha256-xue8Y4NB6j63Ul0wq6fj6PcTrG3Dgju/m/Njb1WEOG8=";
    a0_3_0-2 = "sha256-X9Bzp5mImooiJdx1bK6IQdGsScfCkIhaOXrmnfct41w=";
    a0_3_0-3 = "sha256-EV3OeaKL4zs2KBdZOwfPRg8W/5me7Lx0j4UhLBQjkWQ=";
    a0_3_0j = "sha256-5lZszvNdXDoopjwqNdIvjXKT6jXmCLuWwHL9bJ8Hw6w=";
    a0_3_2 = "sha256-uNWOAnbnYtTz6YsuvV/ymLfNp7Dqdq7NI2zL5T6RoDc=";
    a0_3_2j = "sha256-khnarU0CyEiZKfZj2qVfd5gPGmFPbTlihyZ9lLvBvZo=";
    a0_3_3 = "sha256-VD4KQGn62ebzoGkSTbiJROD3zH3N1OnpP0TNLQPROAk=";
    a0_3_3j = "sha256-k0r/Ls889FEAM60yZiNkIaZh1nu6vvQ5/5o7I6KiJOg=";
    a0_4_0 = "sha256-aP3/Eb+98P/2HqQOKoO8ph8SGF4EsFlwiEI/jpFDv28=";
    a0_4_0j = "sha256-pGkGwPr8JxbFItEo4uoTmYL5uw/ZzB4Nyt6WNAEq+gg=";
    a0_5_0 = "sha256-wLJ1lXGeFDgxttaYk52x1/8Skrs/c9qMKfM4BlaqmoI=";
    a0_5_0j = "sha256-Jtc22Gohcd+KEun6Eshc357QjfGgJ2w7fAi+qc5Tj6w=";
    a0_5_0-1.x86 = "sha256-d3jWQUe68cTst/oqXTcWg5QfOStOXaXW3PQiR1jC378=";
    a0_5_0-2.x86 = "sha256-GNh2+3OoGGv1iIyG+82+EkQi3bdaKHrZ99TTG5HIb6U=";
    a0_6_0.x86 = "sha256-SXZbK9z3UsrKNO2t1Nws0gVGXDe7/2tzuxulYfHeuao=";
    a0_6_1.x86 = "sha256-rfWnsSPGvunJ8rp460dq5rJsnSHXj1IKy3tUt6xpxhI=";
    a0_7_0.x86 = "sha256-j8gHcMMHhTtNM4GH77XT96nC0mSrQyRJlbpCTDRkSvQ=";
    a0_7_1.x86 = "sha256-qKonHYhPaLT1OA8zRWe+Lta+Oaqcc1QYk39Ahu48K1k=";
    a0_7_2.x86 = "sha256-AK4uOzTw4rOwrVIuI8d23ms8Hs880k2hCiW6f1+N16Y=";
    a0_7_3.x86 = "sha256-li1+qwDbmRojRHVG2c9ZwOm0OYKjw+bjkTKftgvOXAw=";
    a0_7_4.x86 = "sha256-fdxa8x0dhtxR6LqEGNFc0VZvHfJMz4b79oUKQoRp0qo=";
    a0_7_5.x86 = "sha256-1SFY4YiKtlwWTIsTXc9kJRXBD9B/m17JqkZPsnk7ufk=";
    a0_7_6.x86 = "sha256-9Ud3he8Z/Y3WvkpyDKQW2D3oKeeDSFO48vKEjH73tKc=";
    a0_8_0.x86 = "sha256-XmUm/EMYycZhgdsBnQQ+b5ppwnkptF/emS9BnmmiGrA=";
    a0_8_1.x86 = "sha256-eO/4OSZ6wksy4NFc5CZB2EbguKR/+9K+l3YvySwqzO0=";
    a0_9_0.x86 = "sha256-dIv9tNzEuYlhRXLBPwymdOBqfXQhkbUOXu0LsxfNBE0=";
    a0_9_1.x86 = "sha256-yULaqMtdZK/LRtS+dcR0NlTJWGQqY7nAF6uBNO+cPDY=";
    a0_9_2.x86 = "sha256-9WSn57r0WvRAUkiS4tp9q2rKL7BKOFe6BpmomYEeuok=";
  };

  architectures = {
    x86 = stdenv.hostPlatform.isx86;
  };

  fetchVersions = out: key:
  #
  let
    version = lib.replaceString "_" "." key;
    hashes =
      if (builtins.isAttrs versions.${key})
      then versions.${key}
      else {"arm" = versions.${key};};
    fetchVersion = {
      arch ? "arm",
      hash,
    }:
      fetchApk {
        url = "https://archive.org/download/MCPEAlpha/PE-${version}${
          if (arch == "arm")
          then ""
          else "-${arch}"
        }.apk";
        inherit hash;
      };
    enabledArchs = builtins.filter (
      arch: architectures.${arch} or stdenv.hostPlatform.isAarch
    ) (builtins.attrNames hashes);
  in
    out
    // (
      builtins.listToAttrs (builtins.map (arch: {
          name =
            if (arch == "x86" || arch == "arm")
            then key
            else "${key}-${arch}";
          value = fetchVersion {
            inherit arch;
            hash = hashes.${arch};
          };
        })
        enabledArchs)
    );
in
  builtins.foldl' fetchVersions {} (builtins.attrNames versions)
