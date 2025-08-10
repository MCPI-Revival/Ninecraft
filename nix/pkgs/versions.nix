{
  lib,
  fetchApk,
  stdenv,
  ...
}: let
  versions = {
    a0_1_0-demo.arm = "sha256-MM6lXfYDNKK8LKnCE825++L7XjK51oZpFACQXnkN4y0=";
    a0_1_0-touch.arm = "sha256-VrmTfTOoMTywFvCrOk9C5ei6XLLBS8zvoji3NvdJWKA=";
    a0_1_0.arm = "sha256-YVCtc8O6HU4ZFfe2mM83V9t0BHyMJ7LsDZjVpS7xVcI=";
    a0_1_1-demo.arm = "sha256-Gu9QhEsYEPNCnGY/D35ns/KWd7AlpqgS8+RUD5aIUoQ=";
    a0_1_1.arm = "sha256-l4N7PnZcgdYWYuBCLDbRIr+9ahxg6E8rzfeiVqpAQsM=";
    a0_1_1j-demo.arm = "sha256-U2aT9jwGV4Iyzl7Bw3OyEsX/Aa/9x+rczm2m4Hl3vj4=";
    a0_1_1j.arm = "sha256-ppeC63SWlPBjVaYHIcQtdrWXfmAARCYngY7uBTvW5aU=";
    a0_1_2-demo.arm = "sha256-RlyqPhNjtS/Xl0l6G7Z/x03g0gqYm6G/Y35kjHcP1mU=";
    a0_1_2.arm = "sha256-gRdxHs5RfIwCmySdGTSiayM7G/u/hrBPfpirgPfefRc=";
    a0_1_2j-demo.arm = "sha256-x4fNTIHxVFGSJl7htiQSCPgKvtR1SWuOU/0LMQVg5Bo=";
    a0_1_2j.arm = "sha256-Hf1qpWOhdI9sQBcf61Y8cZG47RLMZLwpcdHxQKexJcM=";
    a0_1_3-1-demo.arm = "sha256-uApiNw5BNWRwTnY+jnLNgx3tdRLznydLDlJw6jBe8HY=";
    a0_1_3-1.arm = "sha256-GkK10so9wJ33rKIm4WDoM9XDNWVEv9mzI9n2Xpp7m2w=";
    a0_1_3-2-demo.arm = "sha256-i06SUxFBMgpxuuoAFlIr1Vu9GFtdNSdU/eYxcW0w3Fw=";
    a0_1_3-2.arm = "sha256-9SgsMf3GpSOyiczz99Vggn07TYGQIUpOnPuhUfEWdqI=";
    a0_1_3j-demo.arm = "sha256-tTVOVTIL+XVzhHQBH6J/f9A7r+56PBBFOHSHsgef1BA=";
    a0_1_3j.arm = "sha256-hes97aL2T+T3l1LzLq+A45pbfItXnvSinvgQvgoMIUE=";

    a0_2_0-1.arm = "sha256-HVdVtP5aKICnbx33Hb1o8SiuGHXe9JIgm7FFEGvnefE=";
    a0_2_0-2-demo.arm = "sha256-Xyw01aKaEEK0cnF8KYez4tSn+ha8viK5Ej+K9l35v0E=";
    a0_2_0-2.arm = "sha256-WmOu00Hq1sjjTcqfu6FIYNBTsn/75egfC2dPmqc8D2g=";
    a0_2_0j-demo.arm = "sha256-GkvqZsWDQNoIrq3aqTzFB5orWCN4YP+F54Y4Kp8iw2c=";
    a0_2_0j.arm = "sha256-YviYMf0xVkP5g+jJu5AXdyNkQGSFVwzoVAUJZBSwEV4=";
    a0_2_1-1-demo.arm = "sha256-Nfu1rsxPIGinuBbsoXbSJajt19U+3PODev1RmkA4aJY=";
    a0_2_1-1.arm = "sha256-z4gbLiA5edOpINJ9m3bLjJ6TYa0JP1/3HH5o+77doVI=";
    a0_2_1-2.arm = "sha256-hoBw9dc2qDhcaY0iuEnG7EY49KoYPDkVddbamX0IfHk=";
    a0_2_1-alpha2-demo.arm = "sha256-9r04glZR514zVSv3ZRJylt9+Y/WjB5jqxmTrLoUD4DA=";
    a0_2_1-alpha2.arm = "sha256-II++9Xh0QbxNTwNcZ1x09WPD1ZVz57jxZZe5rrX/VR8=";
    a0_2_1j-demo.arm = "sha256-VC7omOXkL8tJqcwuv5UM6wIKIPKywzqfTadu6w3iAn0=";
    a0_2_1j.arm = "sha256-dZAd80sv79Hs8TxVDPPbt64VAdUNe8Ag/9tJSX1h7ao=";
    a0_2_2.arm = "sha256-ZWhiXeJMhTsoNlQkNkxjBsky5eKPd/dQPuoLR0ZQ5aY=";
    a0_3_0-1.arm = "sha256-xue8Y4NB6j63Ul0wq6fj6PcTrG3Dgju/m/Njb1WEOG8=";
    a0_3_0-2.arm = "sha256-X9Bzp5mImooiJdx1bK6IQdGsScfCkIhaOXrmnfct41w=";
    a0_3_0-3.arm = "sha256-EV3OeaKL4zs2KBdZOwfPRg8W/5me7Lx0j4UhLBQjkWQ=";
    a0_3_0j.arm = "sha256-5lZszvNdXDoopjwqNdIvjXKT6jXmCLuWwHL9bJ8Hw6w=";
    a0_3_2.arm = "sha256-uNWOAnbnYtTz6YsuvV/ymLfNp7Dqdq7NI2zL5T6RoDc=";
    a0_3_2j.arm = "sha256-khnarU0CyEiZKfZj2qVfd5gPGmFPbTlihyZ9lLvBvZo=";
    a0_3_3.arm = "sha256-VD4KQGn62ebzoGkSTbiJROD3zH3N1OnpP0TNLQPROAk=";
    a0_3_3j.arm = "sha256-k0r/Ls889FEAM60yZiNkIaZh1nu6vvQ5/5o7I6KiJOg=";
    a0_4_0.arm = "sha256-aP3/Eb+98P/2HqQOKoO8ph8SGF4EsFlwiEI/jpFDv28=";
    a0_4_0j.arm = "sha256-pGkGwPr8JxbFItEo4uoTmYL5uw/ZzB4Nyt6WNAEq+gg=";
    a0_5_0-1.x86 = "sha256-d3jWQUe68cTst/oqXTcWg5QfOStOXaXW3PQiR1jC378=";
    a0_5_0-2.x86 = "sha256-GNh2+3OoGGv1iIyG+82+EkQi3bdaKHrZ99TTG5HIb6U=";
    a0_5_0.armv7 = "sha256-wLJ1lXGeFDgxttaYk52x1/8Skrs/c9qMKfM4BlaqmoI=";
    a0_5_0j.arm = "sha256-Jtc22Gohcd+KEun6Eshc357QjfGgJ2w7fAi+qc5Tj6w=";
    a0_6_0.armv7 = "sha256-UJ9xWMlrDzajRFm0EuewiS0NoVSsltiMk/vaxu05c5Y=";
    a0_6_0.x86 = "sha256-SXZbK9z3UsrKNO2t1Nws0gVGXDe7/2tzuxulYfHeuao=";
    a0_6_1.armv7 = "sha256-lHSHrMo8SxpJdCd4QrQTJDuspXmRYnunvQ9xlW0xAtg=";
    a0_6_1.x86 = "sha256-rfWnsSPGvunJ8rp460dq5rJsnSHXj1IKy3tUt6xpxhI=";
    a0_7_0.armv7 = "sha256-6L5WG1PMytMzP8VnMIi9adTwuf+xG2SymQrBF70zPFM=";
    a0_7_0.x86 = "sha256-j8gHcMMHhTtNM4GH77XT96nC0mSrQyRJlbpCTDRkSvQ=";
    a0_7_1.armv7 = "sha256-YOML0iTT1zjA420M/NoYOBwdzKfci1rsIIbvtJ3W6YY=";
    a0_7_1.x86 = "sha256-qKonHYhPaLT1OA8zRWe+Lta+Oaqcc1QYk39Ahu48K1k=";
    a0_7_2.armv7 = "sha256-qQiBbo8rxs/soTvmiVFi0OLkxH/sZ9yom0OII13rQaU=";
    a0_7_2.x86 = "sha256-AK4uOzTw4rOwrVIuI8d23ms8Hs880k2hCiW6f1+N16Y=";
    a0_7_3.armv7-gb = "sha256-CZ3e1psd8OLLizq27OvfphFMMC+M8S7pI1Bm2mlLHyc=";
    a0_7_3.armv7-hc = "sha256-YiaFMQ+5O37EK/bWr3ux2Eg9yspfq29/cfMW32hoko4=";
    a0_7_3.x86 = "sha256-li1+qwDbmRojRHVG2c9ZwOm0OYKjw+bjkTKftgvOXAw=";
    a0_7_4.armv7-gb-AmzApp = "sha256-0xM5RaNKRChuLOuodeYxFK/DkusedtuQxc940QWyQ98=";
    a0_7_4.armv7-gb = "sha256-N0KXXEUp6lYLg1USJjxw1aHhIbim1jA8lw+aPfnAZ70=";
    a0_7_4.armv7-hc = "sha256-G4U8jKswTcJcoFLxl3IvFLkWrdA+TKnEV3cGbhmL76E=";
    a0_7_4.x86 = "sha256-fdxa8x0dhtxR6LqEGNFc0VZvHfJMz4b79oUKQoRp0qo=";
    a0_7_5.armv7-gb = "sha256-ld87zFXKsxDjZkq+prJI6dCOG4glnJl62m7059iO++E=";
    a0_7_5.armv7-hc = "sha256-bvKTbauFs32uKXmMmqtRZjCMYvuHf4eYnhUDi9YE14Y=";
    a0_7_5.x86 = "sha256-1SFY4YiKtlwWTIsTXc9kJRXBD9B/m17JqkZPsnk7ufk=";
    a0_7_6.armv7-gb = "sha256-lgcofvCRXVs3YnTzU14vRhXRLI0JGTMRrkjGLg3EuNk=";
    a0_7_6.armv7-hc = "sha256-uG/pExnOMSSvblDQ/9U/GR7oT+K4vHpfkxl10UvIMG8=";
    a0_7_6.x86 = "sha256-9Ud3he8Z/Y3WvkpyDKQW2D3oKeeDSFO48vKEjH73tKc=";
    a0_8_0.armv7-gb = "sha256-Ty4u8zcEIEdkKgVPdvJvn0qMdkSke9QnC/Yc1ybeIro=";
    a0_8_0.armv7-hc = "sha256-FZ2vrU9h/yQg60RPU5kpIFmcPN0v4dl0+SQVEEq3L28=";
    a0_8_0-build2.arm = "sha256-VoXG9ipEp1aRgOX7Nu7P/IRYtEC5hv0WkFVXj2tmRS0=";
    a0_8_0-build3.arm = "sha256-+CE4b/C7VXRTuxgV29zXvoYCjU0iQ0tXTcCKV2R5Cis=";
    a0_8_0-build4.arm = "sha256-epe0HqfH6S4xtaFEdGWK/oa3FFYNkPZ6SiXcRQa7vG4=";
    a0_8_0-build5.arm = "sha256-MkrpEEFvH7iqwmvFBUbgQ3hcDf1UMcQCJZoS0ZDexJs=";
    a0_8_0-build6.arm = "sha256-sbMPJFZ+7sCpxztNBk3SSKZd8eMVqXZtU09wupbQw50=";
    a0_8_0-build7.arm = "sha256-ryDi6qsD02n0NgncgEM80U6QX1a9uMiX1AQNlIt/weI=";
    a0_8_0-build8.arm = "sha256-SCoMl1KOfngFX5UrdkciFEDX8f+IvqMpe1UcG/DrlVM=";
    a0_8_0.x86 = "sha256-XmUm/EMYycZhgdsBnQQ+b5ppwnkptF/emS9BnmmiGrA=";
    a0_8_0_test1-alt.arm = "sha256-/J47jEvH7PCo8m7AxvJsf0zEyPyu+HaF+QqRKku0Ang=";
    a0_8_0_test1.arm = "sha256-BT/ZmTyNxoTz9qEwZAVEYB5B8AXgBpvswvBE34RAVXc=";
    a0_8_1.armv7-gb = "sha256-rIuNMi0kjNsh1LrttkxwJHCx37oGa6O+Ded/gllqkDs=";
    a0_8_1.armv7-hc = "sha256-ged0StFk7jI0941RdTe8s8bKq1ZUnQknuKrQuQdXpiE=";
    a0_8_1.x86 = "sha256-eO/4OSZ6wksy4NFc5CZB2EbguKR/+9K+l3YvySwqzO0=";
    a0_9_0.armv7-gb = "sha256-Q8GFMq4QxmkXIIdXIdDog42bVQ+C6WmAalapRuLExoQ=";
    a0_9_0.armv7-hc = "sha256-/9GVUhDKELhd4y3BcIfR6maC6gL21sWaZSs7JRWWDXk=";
    a0_9_0-build1.armv7-gb = "sha256-gl3d3e0xnjyvNoMaa4jr4uiTaD+4usRL2Kq+xCOwRi0=";
    a0_9_0-build1.armv7-hc = "sha256-t4AIHA234if4AktH9LCa1YM5Ke6+lELQDR9FGRo0wPo=";
    a0_9_0-build1.x86 = "sha256-dIv9tNzEuYlhRXLBPwymdOBqfXQhkbUOXu0LsxfNBE0=";
    a0_9_0-build10.armv7-gb = "sha256-cDvaVDoCRIa3oY8Fcpi9DaGK8wEUUjj4mkEBSIODvgA=";
    a0_9_0-build10.armv7-hc = "sha256-Vq0gp2YK19QeBVEEhZTIsvylPk3QydCNlDc2cFLIY3I=";
    a0_9_0-build10.x86 = "sha256-z4FZqvixHFM+q2tIuJo8XZaayKByBkyPWa8I9B85vPE=";
    a0_9_0-build11.armv7-gb = "sha256-UxCa4f8YTYMO9/IeJR2D4k+tw3SxOd6M2AeDTA6Stzc=";
    a0_9_0-build11.armv7-hc = "sha256-t1CRmQyWOxLQlCmdG+r/lxbbAFkfGwx1jGAOzZ62//Y=";
    a0_9_0-build11.x86 = "sha256-m1RzHusXoEzJ/uWzDqLbqvM0japL0mVkw4qR021U1CA=";
    a0_9_0-build12.armv7-gb = "sha256-lhLOcL6OyoVgB+jhw1una0ySsfh6iveKLox/PKJJozU=";
    a0_9_0-build12.armv7-hc = "sha256-7cQItHMGitTn/avR1XrgxtsDAgbcrxlNc42T51OSPZ4=";
    a0_9_0-build12.x86 = "sha256-mb2H6iJ9dmJGjhcCL1fC8QDRzmZALHN5I66S3G7toIE=";
    a0_9_0-build2.armv7-gb = "sha256-Brbt5zrjtMCiW+frVnXuxG+WSwMur+p8fxgaM9CDxuY=";
    a0_9_0-build2.armv7-hc = "sha256-6wsliFmcRF7GD+meAkykuxdATjwBfR15DxPSHze8gXg=";
    a0_9_0-build2.x86 = "sha256-NBgZOWdyp/vhFV0OmqCUDeVvELpOzFxhkhMGEvuLo8M=";
    a0_9_0-build3.armv7-gb = "sha256-mZCoBvgsor5tbCqISWUySHsuW6YHe8uCEGskWLtrQ8g=";
    a0_9_0-build3.armv7-hc = "sha256-YapRZSdFwkIWyu8ffVDi6UUAp1Yn+XaS+DrDRiAXxsg=";
    a0_9_0-build3.x86 = "sha256-dNHw0Nb3wITjHX684iIwrNFxZia6767bmQI1fSisB7E=";
    a0_9_0-build4.armv7-gb = "sha256-jfcmq/N1z0Egi+gBLPNqLoIVxrrSbvACFHD7KAuY7OY=";
    a0_9_0-build4.armv7-hc = "sha256-Rz9/ftkkdJdj5QA5AQLVNbSMUlSaOKsjsl2m0VM9puY=";
    a0_9_0-build4.x86 = "sha256-z5IS8d+jUlBrk7eA5Fnz4Uf6K+Jqr2EYDOhEqVwTVLg=";
    a0_9_0-build5.armv7-gb = "sha256-8m/fJBQ3qFAF7yXSHbn5t1/MPTDRl2SL9AAs74bELQc=";
    a0_9_0-build5.armv7-hc = "sha256-Lh4nMDANCfLlC4CmqWKy2CJL0kDpBXKE6cC5577v/e0=";
    a0_9_0-build5.x86 = "sha256-yG3eoUxeIvcKbNy85b6I1CI/yd0jg18xWP61dumMucs=";
    a0_9_0-build6.armv7-gb = "sha256-k7ck6gM1FfQr80BZ49/C7hmvdR7Rh4RdhJaEAQrFsKo=";
    a0_9_0-build6.armv7-hc = "sha256-fZmcHhm/Nr27WKjbFgBjvNayo5ahX+7p8Hg9xruffLY=";
    a0_9_0-build6.x86 = "sha256-PTZcCmAgA+wzIzajSoQtLRFtrMXtjbmKaUrT1ZIIIjg=";
    a0_9_0-build7.armv7-gb = "sha256-1Vm0l+ZUX+9prgO9ayoR9Ni5yCVwAqsGwFiJP+meNOA=";
    a0_9_0-build7.armv7-hc = "sha256-UA/MmdRpShZ7D1BzB2Q2h8pf2HNZqWqhsD+814qSGSc=";
    a0_9_0-build7.x86 = "sha256-G7zA481HhcUVc7cxHduP0x6gz2/6xqCnJjBUgFxnZwk=";
    a0_9_0-build8.armv7-gb = "sha256-l8rY92olQeyHN5qgPKUKZ5zVQg+WfOSdbQh6gyHN/tE=";
    a0_9_0-build8.armv7-hc = "sha256-imtVWLLDbRNlAvMX9QfYsa05dBxhfAKIiD5rhv2BSDo=";
    a0_9_0-build8.x86 = "sha256-xldDuyBiP34JvHBav6UxY+NIs6FCG878YVyqTkBXS8o=";
    a0_9_0-build9.armv7-gb = "sha256-lXX36OB/pL9Z9JXIXOJh7nlJAmb5kyCLWePZ/606erA=";
    a0_9_0-build9.armv7-hc = "sha256-uIewemKTNt00ZQJbxu+lFGYS3o6+ePxytjxYMZH9tms=";
    a0_9_0-build9.x86 = "sha256-swiLO4aM3tj92XZ6rsZ6RO3OAC11hnSVpXvIYVqK4nU=";
    a0_9_0.x86 = "sha256-dIv9tNzEuYlhRXLBPwymdOBqfXQhkbUOXu0LsxfNBE0=";
    a0_9_1.armv7-gb = "sha256-8HuT/vB5X7Tkf9eNwcGZmvuQb+llvENqOuF7uKDUf3o=";
    a0_9_1.armv7-hc = "sha256-sknx0zllYmnaKaBjksDrm4s4NUw4slzIZoanElefRkM=";
    a0_9_1.x86 = "sha256-yULaqMtdZK/LRtS+dcR0NlTJWGQqY7nAF6uBNO+cPDY=";
    a0_9_2.armv7-gb = "sha256-iGGXgIADuC6wKoEUcHhhJwEhP4DpZWZH6FFXuzqrhu8=";
    a0_9_2.armv7-hc = "sha256-WLZnZCqzTxUXP2SxFzAB8VaPIc2aHznPd8Czc89GqIw=";
    a0_9_2.x86 = "sha256-9WSn57r0WvRAUkiS4tp9q2rKL7BKOFe6BpmomYEeuok=";
    a0_9_3.armv7-gb = "sha256-46ycVeywiOE2DEh4bgKl/m4b36L2D75kySxKjcE9kNE=";
    a0_9_3.armv7-hc = "sha256-aDMZjmx5lvtGml+9V52nf5hPRp7xI7Wg0bqMrju+SmQ=";
    a0_9_3.x86 = "sha256-HKrw4jhwQE1toMIO3oAQFlzlMp17dmqLowHy7ha/rdE=";
    a0_9_4.armv7-gb = "sha256-5KLlC/yhBUO3OcZTyry9KbFhfmsQpMJhxLHV819tX8g=";
    a0_9_4.armv7-hc = "sha256-C0zGI6uSt9EPZNlPukLpAU787ELWy4C/capMNXZmeno=";
    a0_9_4.x86 = "sha256-h4rNd1etOsqHUY2aiLfusHkw8yIdtxZaV3GtzbA1aYw=";
    a0_9_5-1.armv7-gb = "sha256-bhx+nLT60hEXuh1OBn/oKjIW7H+TmKI4OYuW3uGWVWw=";
    a0_9_5-1.armv7-hc = "sha256-qBGhNBn0vdixuPrhfFEzISWRki14TZaapBgf6H9pWko=";
    a0_9_5-1.x86 = "sha256-kkNE1x0BmN+zsA/fVB4TFuTbxYQXSFBOaEJcyGMSg/I=";
    a0_9_5-2.armv7-gb = "sha256-O8MCzdDKZMDGSYMfCkcXdWb4f/0tJWHsabxyXgC79eQ=";
    a0_9_5-2.armv7-hc = "sha256-pCIYj1KJCTqskhLZYv33ZvJv1nEmKkauWctpYF+1fP0=";
    a0_9_5-2.x86 = "sha256-pHLwH1/zFsSEK84X0OxaeUpo2jlbpmN8Kb5X1gX6iCk=";
    a0_10_0.armv7-gb = "sha256-mPUzNQuMY24Yrseb+jU9qRTP96POcSqp+DeiWkRlK9g=";
    a0_10_0.armv7-hc = "sha256-x61djZSRDgq5vvQkK6alMtItsUDXEfZEAHjNOCemJ00=";
    a0_10_0-build1.armv7-gb = "sha256-r7gtg9JHFYmCX5Mgl0GCyRlx0rtIoTj/eguKQGvFel8=";
    a0_10_0-build1.armv7-hc = "sha256-Slb+t7jPfi3cPuj3wunFovkY3in6HL/kEj8w0xUCPzk=";
    a0_10_0-build1.x86 = "sha256-cpsGtflX1FjnYvzENCbfkJWa0fjSt6sX+Uz0VigMBOY=";
    a0_10_0-build2.armv7-gb = "sha256-f5jOmr0vHt4xlWcEFHC1b4rR9xnXVETPAp8+np1PBE0=";
    a0_10_0-build2.armv7-hc = "sha256-oQtL2TdQHmjpnmTM9JRAcp6kbsaZh4l1Yx85HRjkhtQ=";
    a0_10_0-build2.x86 = "sha256-dm746d/svrtiHEeFqriXDw8M00X/c/QEKaM361LvxbE=";
    a0_10_0-build3.armv7-gb = "sha256-m8xU119eFx9bp6X3SVNu3PkJ/EbwnU+CxMG5NuBwA8E=";
    a0_10_0-build3.armv7-hc = "sha256-c8ZvlvfzaTE04q6ZOz0HH9ZAKBvWH+sEDvW25+7IzoM=";
    a0_10_0-build3.x86 = "sha256-jyYVCVg/CNX8YyD7GKVIC/vHWQ1qw9NKSa0JJpehVBk=";
    a0_10_0-build4.armv7-gb = "sha256-4TcPPMlEUjaV+DmwKP4RjUlYBwl1HPuTVkX+1zGStQI=";
    a0_10_0-build4.armv7-hc = "sha256-cJDzUrjpGBJI6n1REMons8QkCTvZ5FNg/SCfmkyVX5A=";
    a0_10_0-build4.x86 = "sha256-iQoGXAIV7jDhappUwE27Zifrziyy2d3SUNY3wqvDJIs=";
    a0_10_0-build5.armv7-gb = "sha256-WAxxPrjJ+mwlF+ya39sTWUKkSzD5aWEdDNm+5Bk0Yf4=";
    a0_10_0-build5.armv7-hc = "sha256-C1vuu/HuyZ8djR/5lGFnUDw6PXtc0nPVJU51q7Qrgns=";
    a0_10_0-build5.x86 = "sha256-YER68JfzCF8/1cnDf/aqrR+mOfwioRDHmqpDZva85x8=";
    a0_10_0-build6.armv7-gb = "sha256-iGOvUu/Vg8WpRwELfl4FA6zYaeD3M2tbYqzl2ZI9WrM=";
    a0_10_0-build6.armv7-hc = "sha256-cyD4eFboxFrphJS0Rn4NvXSJ1f+jkN/P40/TcpD54Pc=";
    a0_10_0-build6.x86 = "sha256-ULkWTX/ZOQyBnvW32LV0EB3Bm6TwY+66rNLfBGuHsg0=";
    a0_10_0-build7.x86 = "sha256-6JD3gAk7I2M7wUH8OG3QJKeWDcjiN7Q0HisHInZ6K8k=";
    a0_10_0-build8.armv7-hc = "sha256-QGEh9aPkdygnwhyz7abW6LZ+dIyUBJntXJpPhV1PO+A=";
    a0_10_0-build8.x86 = "sha256-RwSeXblT770AkSFmfv8yAhHGcqevi7zgb7XPTIU+zOU=";
    a0_10_0-build9.armv7-gb = "sha256-JinG99izx0Z+QzFgoKi3yDGXKgfQYkf+HTFCmW0v8qU=";
    a0_10_0-build9.armv7-hc = "sha256-2Ay+Q4wamDUQWekU2jk7e4JHFpR1rhYS3mF7rNK45+g=";
    a0_10_0-build9.x86 = "sha256-JF5bAjv2VYoiwGdAhSReIeUPVksrDFSbib6SlJVfCfo=";
    a0_10_0.x86 = "sha256-AjHnXDhsXFbOoW9Y/uHIE6RRo9OwU+m0DP+pOlujRDE=";
    a0_10_1.armv7-gb = "sha256-F+j6lNaXsRcXjGocwf1cT/R5gKvQ5MjRFKslPPOPu7Y=";
    a0_10_1.armv7-hc = "sha256-0vENKLdGvUTfz0DLAtzGrnzMcTuZCOEpDI0He66fhBY=";
    a0_10_1.x86 = "sha256-lY02s7BMUgUIMOQa62gz1gdcLZVN9fuUsVstjWZ7ido=";
    a0_10_2.armv7-gb = "sha256-eKsaNKATc2HK9B9l48CwpHIyPofVrQzgFCuJxtd1IF8=";
    a0_10_2.armv7-hc = "sha256-SBVzEs6cQXhQoRSU/xgxk9FMqek3y+bGEYCWi2e0r+M=";
    a0_10_2.x86 = "sha256-5DfA0J2W2S+UKlbOuAmUdh466ya59zn1IkI6GGqqvIg=";
    a0_10_3.armv7-gb = "sha256-4LUbfeR+EB94LLIR/l8tE3XBczVf2CQN50zAJM7S7go=";
    a0_10_3.armv7-hc = "sha256-u5yD0teysohO/EQDoDn8w8F+ANSMSzHJOTHxud4A11A=";
    a0_10_3.x86 = "sha256-u9oGXL0Ui6iToG1+5UJmXy1e2DhnvTuU0hh65FMdbCw=";
    a0_10_4.armv7-gb = "sha256-EuqdYvhcjUPHmNmH/rPT9k/olc60iYT2NolnrEIDUks=";
    a0_10_4.armv7-hc = "sha256-Y5ERk0SBCcjdqPgDjc1HR+JxZPN+R2PG3WQpAJLXDtU=";
    a0_10_4.x86 = "sha256-Yk8WBgxDt6Qd3ikoS8v3G/6zfEz7XvxAUJ+hhG6BoXM=";
    a0_10_5.armv7-gb = "sha256-fPaIDeyqswu8RoKtiu4B47rd5AeYW7x/aivrrI0XI1k=";
    a0_10_5.armv7-hc = "sha256-e8gccztsZk1PWDKsjN4msQS026U/y6vkYWzlcDgTOdE=";
    a0_10_5.armv7-jb-FireTV = "sha256-WOdAZHiZXIxv7RqnwpH2iS/V00anSFRow4P8IAY1ATg=";
    a0_10_5.x86 = "sha256-NYqPTpspSTqDJJD4k/x6FN2Vd9IpR295nrBAj5/F11k=";
    a0_11_0.armv7-gb = "sha256-YqDoGIRVojyp+uU5tWIuZQn0G+IIf++yk2JH1ENAlKk=";
    a0_11_0.armv7-hc = "sha256-RtepBcUg/zW+jle5DP401VfrwmskfukwckpvNUGDQH8=";
    a0_11_0-build1.armv7-gb = "sha256-vySnKVutmTERltOY1v5uV25Qlvu8IVmAAoOuSU1mO9w=";
    a0_11_0-build1.armv7-hc = "sha256-01eFiKDgaXiRhA0ZBTVEiuq4vY4P943jooF/cj/9WfI=";
    a0_11_0-build1.x86 = "sha256-ZISyi/KBzhQ20q9l78LrfhTra4+tzwsq7vKfszsRmwg=";
    a0_11_0-build10.armv7-gb = "sha256-DhOceXeshPigWEyxSSurEKqsmdT3ueQYU0BA6dk6Ivs=";
    a0_11_0-build10.armv7-hc = "sha256-prC6/QvGPrAkwj7CS4XYJVTvlG5PnEWrKep+mTDeVuY=";
    a0_11_0-build10.x86 = "sha256-4mKmk8KLuTtUk9NQXpIPK5srKfPrYMS2CHcORcqcPDo=";
    a0_11_0-build11.armv7-gb = "sha256-obVF92zC5OdIXXUPD+gqIwSg0y7A0YbRzcT/jVP1V2c=";
    a0_11_0-build11.armv7-hc = "sha256-sUSq9cS1jMOQ378yCZMGiNSeyRAFYRBtTbuYQylTdxs=";
    a0_11_0-build11.x86 = "sha256-99MuGzoLNeVw0/a3PZxy6d8iF6af9uEPPZ8lFrzxgu0=";
    a0_11_0-build12.armv7-hc = "sha256-xplMSmtW84MK1DYD6N9kv6m2FJJsusIlUllkhtxAtrU=";
    a0_11_0-build12.x86 = "sha256-S9pHsUOfzF+vzEImThAW/AA0YC+5RBTmcxL+pW15rDU=";
    a0_11_0-build13.armv7-gb = "sha256-FNPeaEw3ziW7e+Xrlqv/0J66yvJLSE0jYanoXRrEAlM=";
    a0_11_0-build13.armv7-hc = "sha256-5QH1Y8eG3GPB5mm0WXNx1WF989VffruT+sEV8PQPUrU=";
    a0_11_0-build13.x86 = "sha256-IvtBA7n/OqyQfp326J7EvlSlEDxQkGPmgr6YvX4i6IE=";
    a0_11_0-build14.armv7-hc = "sha256-7btcy3bladXoT+hnTvqJflCNfyUxdVG2cjH8TeLynRc=";
    a0_11_0-build14.x86 = "sha256-FcHW2hWCAe9dBgzF7hLvLm3nlc6oy563oyjwvGKHisY=";
    a0_11_0-build2.armv7-gb = "sha256-xy6Hqt5Q6rkAM9O97r/eOpUSEskkaYVMePkK5QDoHHU=";
    a0_11_0-build2.armv7-hc = "sha256-2FGaz6RXtEk/NV7jH985CAe0ghcGFl+o4+6cO/GuZnw=";
    a0_11_0-build2.x86 = "sha256-YrZwGrbQhbPgoucSe2ExdvfESHj+SvU45VfG67RY6q8=";
    a0_11_0-build3.armv7-hc = "sha256-mhXtNOTqYT4admWEA7dzyfnFptD4++HbtYt0YG1tKAk=";
    a0_11_0-build3.x86 = "sha256-3EEhjaXocqUNz/CJqag+FndXKQ3px407kGzfUxTyhv4=";
    a0_11_0-build4.armv7-gb = "sha256-WKtE1ugSS0yLVJj/3EjVJv324n4SilLNT8bKKLeWxjY=";
    a0_11_0-build4.armv7-hc = "sha256-+lRgmAWte8KfMB5OKtHhall2wIA59nWGiFIqqIDaQgk=";
    a0_11_0-build4.x86 = "sha256-w6LiEIrjswAs48xBnHbVr1SEaFvk/skf//8+cmPDhJU=";
    a0_11_0-build5.armv7-gb = "sha256-alnPn1glmNxHhNGzJkwNBQmPc8sQ7O8BNAYTv5jFDcI=";
    a0_11_0-build5.armv7-hc = "sha256-ERlMhpAOCGRmEIswGwFaLQIDRFkhpH0g74oeq7aVIRY=";
    a0_11_0-build5.x86 = "sha256-PYyEEN7c5QdiIrOdAYjX0c3ECxpUk9947wFWX4ezryQ=";
    a0_11_0-build6.armv7-hc = "sha256-lT5SvcgKacq2Gehsx3yqiuPSRobx6ud3TaRiW+XsEQc=";
    a0_11_0-build6.x86 = "sha256-kmO7Fp61dE/45qS9NCG572lFDRFiXTtLi/zfwOOq1qA=";
    a0_11_0-build7.armv7-hc = "sha256-OICtC6cpZ0FlU/3my7rOChoD9Vyzqk7vh1hQ7+KCnDM=";
    a0_11_0-build7.x86 = "sha256-MMu3j+Dx6mYeOd0QSjkEWzjAMnF3LfPZ4Z47Knln0rY=";
    a0_11_0-build8.armv7-gb = "sha256-UQf/kVEML2qaodrQbcp6RGks1e5TF4RSa289JRb7LNc=";
    a0_11_0-build8.armv7-hc = "sha256-fIHpxuarINakWs6Lef+QGz2TyWsgbwhwMkW0aA/MGYA=";
    a0_11_0-build8.x86 = "sha256-LH3z3ilDB2+o26ddsNq496EJmFleTJuW7i6bytIbw5I=";
    a0_11_0-build9.armv7-gb = "sha256-ObAXyC21vaTBGY6VzuWCySeK8GyPhROBKthq/sd9ECs=";
    a0_11_0-build9.armv7-hc = "sha256-iel8vS+Cko4dqlmCl7ftCTHuGNOPtGVPhxpAyhW7pNk=";
    a0_11_0-build9.x86 = "sha256-VxRPj4Eu4XRQrYvci0V/V+P3KR7CmjVDcVakzH+/CEs=";
    a0_11_0.x86 = "sha256-/t/jayOzoIpJT7u+c7DfH59KAaB+STTrut7v5lxuSls=";
    a0_11_1-1.armv7-gb = "sha256-lvKdPq8C0F0LyrFJ1ZOweqU9s+ptHUdV2Z6dv7+lyf4=";
    a0_11_1-1.armv7-hc = "sha256-xSmid9fWg0va6xvbupxD0YUg1LXNPoJmCfQxO4js0T0=";
    a0_11_1-1.x86 = "sha256-Oct6PF20O7mFpiN6B3hdt8v+J8nCZZ388Xbzq4jbV/w=";
    a0_11_1-2.armv7-gb-AmzApp = "sha256-28y+9fmfAOxS5F34l5F7NVt4ErTmSJIp0ysigdP1Qxk=";
    a0_11_1-2.armv7-gb = "sha256-7yJ5/mChHEnUHfsHrwOiOZFxXjTRJRCPNHztDJ29bLM=";
    a0_11_1-2.armv7-hc = "sha256-tIJ3bpMfo3uwMaB8iO7J2pq48jYAedTzJdTJD64fXwk=";
    a0_11_1-2.x86 = "sha256-wW60g6OcVFEPZZw7NSNYlUoih3OpJrZq4rQi41WrP0I=";
    a0_12_1-AmzApp.arm = "sha256-9JF1QRhR7AiAbwhx6lBRbJInhgih9HSRppphbOu5Q2Q=";
    a0_12_1-build1-gingerbread.arm = "sha256-rZtUOCV1dYJkiJIXPJyW44KOTLLh516Bn9hDGGmnAZA=";
    a0_12_1-build1-honeycomb.arm = "sha256-LVbVAZyXrsXZji4xs2zaoz2JrUhzOk5erFYKnWiNvNw=";
    a0_12_1-build1.arm = "sha256-yWbIKcvmUYPrKqsq1+jc/A+/btDiN/aAmpCMjmfOvm0=";
    a0_12_1-build10-honeycomb.arm = "sha256-JAaKVss3JCz+7f00AHdHhDtUJkheImyb6m74XNbhhJY=";
    a0_12_1-build10.arm = "sha256-FDvjW5waRqiVRM78Yu+THSt7phBr5uKJWBCGtROiAnI=";
    a0_12_1-build11.arm = "sha256-Z1SwgHEUNgOFyGI43NsNHTamNFyIMoNcxIhOfVZzjXU=";
    a0_12_1-build12-honeycomb.arm = "sha256-bpfS/4MJljwydqMVZuS6tZorEqh+GrUE/ITBQB7XKeQ=";
    a0_12_1-build12.arm = "sha256-GerDSQEUJWDF/kJLZxavSB7/VzmdxuzXG2RbNsH07HM=";
    a0_12_1-build13-gingerbread.arm = "sha256-akPmQXJYDsN0DBGLmKyV2RpbqxUXb3FAugqQHOtRqW8=";
    a0_12_1-build13-honeycomb.arm = "sha256-X5CDfU2XsMTmWiXn4P5G7lNUDLJ/TKP5z5NSM9H/Nts=";
    a0_12_1-build13.arm = "sha256-hn75wiRcXDKXSWZqK6CyV1I2lY8QMbUK5PPNuRA3qR0=";
    a0_12_1-build2-honeycomb.arm = "sha256-E/3dioYKCB2s4P74qojuFOMZL5Uly3MmBY1JdbT490o=";
    a0_12_1-build2.arm = "sha256-8bK+gpPNNVLANyHooepXKi1WxMFC1bNgN9szCP4nffk=";
    a0_12_1-build3-gingerbread.arm = "sha256-dFHuY4NlcXVYBFXAz5mqu7D1lyD1+9olRBx+lGs/xQA=";
    a0_12_1-build3-honeycomb.arm = "sha256-S27EtwqbPsbJgYQ28upiFogFi/p7ovPfKRY+JI6yzl0=";
    a0_12_1-build3.x86 = "sha256-/PVxUm8wE/kmwBVArIoOYlauKdY91+T9GrGHqqBHUYE=";
    a0_12_1-build3.arm = "sha256-r4Nh7wM7XsLNV70o5eWoYOqb82nG4XPBFBoRC6EJJsg=";
    a0_12_1-build4-honeycomb.arm = "sha256-lWwPYJVROsWAwOHprrTryDtX6AQYoVTuTgcFgrL4Bj4=";
    a0_12_1-build4.arm = "sha256-uCWvXhmkrB46KjNH2nEskq9be1FvazxsRCDxo7OYg3E=";
    a0_12_1-build5-honeycomb.arm = "sha256-JPufAf5z7WCZg9lDDx2ZyAjZwpGkmxtRpF6fCCGJZxE=";
    a0_12_1-build5.arm = "sha256-tHvtOj+QtAKDzMN4Bil7SR+XSC4u3NQpEy0e0HN42C4=";
    a0_12_1-build6-gingerbread.arm = "sha256-xIatVoF28mhVHxdz9qRYYr75zNmASnTqmWIwyoBfz1c=";
    a0_12_1-build6-honeycomb.arm = "sha256-0hUSfbk8mM77NNZb3D0UrvtSjjgcoilGq8gNIOW6QBA=";
    a0_12_1-build6.arm = "sha256-lycjuvZSst57yMUSauuhoyVZWSe3uWf4dkGhCQ3mM4k=";
    a0_12_1-build7-gingerbread.arm = "sha256-fSs8faquQ4e9ILJ5ttnoMhW5nOwOFnILDZNAbufCwto=";
    a0_12_1-build7.arm = "sha256-RBneLfW6mriA8xxr4ATvwGr796R+3owNcZA/ZYIq4lg=";
    a0_12_1-build8-gingerbread.arm = "sha256-OYhA+d4HixMp9GUv0dXisW78AGKb8axncobvPGiKRyU=";
    a0_12_1-build8.arm = "sha256-VL3kKVeg3LB6kQx+ydnR06uBuY0ZZDkjHRCVrrx8agc=";
    a0_12_1-build9-gingerbread.arm = "sha256-+0mUsOSu2gzoo4l1pWf64lwa7r4SS1C02c3Efbz0CzY=";
    a0_12_1-build9.arm = "sha256-Hp3MsfEJEi69NYojmfCZ7iZMffd+6ytdzS7U/FZ0fAk=";
    a0_12_1-gingerbread.arm = "sha256-uwOHDjLh6Yd76DmNqXnPOYBuFSyHvPvkvUKDyycchq0=";
    a0_12_1-honeycomb.arm = "sha256-sIkTdwS1599WAfY86rUrrjwVYFb1avJkVuAmDFnxjzY=";
    a0_12_1.x86 = "sha256-eXPsUkmatYF/u4NDd9CscynWegZrMoRHFbD/qKPtEfI=";
    a0_12_1.arm = "sha256-jiAlPIoJv7aTZVHzMI8iyC5lOoKUbQRrF1fTOznn0Uw=";
    a0_12_2-gingerbread.arm = "sha256-BigEnm9ou/kq81KPi1+YrPQZvibBWWpf2G65fyDqoPs=";
    a0_12_2-honeycomb.arm = "sha256-NNQRcCr/EemiSFGumsMedppK67js0uMoIQCEkxdfvl8=";
    a0_12_2.x86 = "sha256-VXwETr8f2QXcAyFq9KNni6j8g+pffhhPzJ0Mmyz6tmM=";
    a0_12_2.arm = "sha256-TyvWD5Mxk4P6e67peA/EEKZDAz1VoYAp6vo5kqA0KjM=";
    a0_12_3-AmzApp.arm = "sha256-EXZwpIs8TtDkmkJ9lEF92DAY0fCAHZNEBGcXtNzGvUc=";
    a0_12_3-gingerbread.arm = "sha256-rG5TsK9DgCDYQMDgC2AcR8vDOOBpVnOmPVGRqukFvzM=";
    a0_12_3-honeycomb.arm = "sha256-bLChUmg++rMSYQdumdWOlBL+Jas8+RojHFUQ8ZH5h+8=";
    a0_12_3.x86 = "sha256-cA4Wnj+jKODXYzRrDDpV/2HqcgL7PiecA5kRAkqXGdY=";
    a0_12_3.arm = "sha256-+m54lEWLSZyp+cXrWA5jjoyWyAFk1lECWu8KLLvr19Q=";
    a0_13_0-build1-gingerbread.arm = "sha256-vFbDEaLUPQz3VM7WZTmzzTKrG7XgwV64gbedL69ys60=";
    a0_13_0-build1-honeycomb.arm = "sha256-c5PpNy3lE44zSrx55WG1k0Lq00RFt2UGEL0kcpEYlCI=";
    a0_13_0-build1.arm = "sha256-FL25ceigE4jGTfq1ehLZP6NKWgPvLxE7UCulMoC66U4=";
    a0_13_0-build2-gingerbread.arm = "sha256-8prh2PuX849i7GEvOzPM6bus7y0gHxf2MPZDHCZlIaw=";
    a0_13_0-build2.arm = "sha256-2lk/wFP1J4ZWsdbhQAEuK20ImvJrCwY1iIJMFtBb6rM=";
    a0_13_0-build3-gingerbread.arm = "sha256-WPPrU22dVsIoOZeaE3q3noNwlZdP2ITHEh5v/zYNTm8=";
    a0_13_0-build3-honeycomb.arm = "sha256-ZMEropFx2GgXeuZPDowyQJAFNOoXeEN8hfRM+e0eyXQ=";
    a0_13_0-build3.arm = "sha256-zpuCI2qOQ2OffRJtuH1sFUgGX4eGOCXNmioQSdq1XZo=";
    a0_13_0-build4-gingerbread.arm = "sha256-KXkWMNJKwCfm30s+5Vtti1W1CS8K20hlRVVl1HRVw8U=";
    a0_13_0-build4-honeycomb.arm = "sha256-UMNN43x+p1287tGiySnEq76nT2JV65okk4qEskfZut8=";
    a0_13_0-build4.arm = "sha256-P9pRGWyRV4G0l4WufK/sNnPDXy4nKDkgInMaS25w2BY=";
    a0_13_0-build5-gingerbread.arm = "sha256-mpXdJxhjeJYv0Gxd8EsSsTx40BrxVzb8F/7qp++WDZA=";
    a0_13_0-build5-honeycomb.arm = "sha256-a3WVq8XiAV0JcGYMR7P9HrZPqXK2HSWMOqL3TDxdKKY=";
    a0_13_0-build5.arm = "sha256-XvFxfseLZgUSr1BiuW6JGrK7j0hssHYeyznpkMs/JSY=";
    a0_13_0-gingerbread.arm = "sha256-/LbnHmWewtAoyEHBwxM56fQw0N7vhN5NFE8WBxGoAC4=";
    a0_13_0-honeycomb.arm = "sha256-L5gBsgyYCtITk/PeEJB1kC9F/ZVSCO2Rw1buB7rswks=";
    a0_13_0.x86 = "sha256-hEXQnl85G6MZT130/sHHG8gcctx7h9Lhz+QKci30iKo=";
    a0_13_0.arm = "sha256-44tTms4ypTKIrZW+Dd9qBVCVArsTWfPdLz8VOFXJvXk=";
    a0_13_1-gingerbread.arm = "sha256-0TEDBot0A4MQYvtTb/QHPcIStAiyb3gpCjS/ikkQkj8=";
    a0_13_1-honeycomb.arm = "sha256-2Gas4A95KgcmlENRCyrRKqvmyOKuhhLyaPALCWI1olw=";
    a0_13_1.x86 = "sha256-hvVbEcga1okF3MBYRP0ZDeUO+n2EGAyF1UwoTKYIKVc=";
    a0_13_1.arm = "sha256-MOezKShRE5A7A+S8+0qpe64wydsdE9QqZOnjd3K6utw=";
    a0_13_2-1-gingerbread.arm = "sha256-87+C1vwYdMXWyMdSoNk7SIDxQ7M/NsxASjhEnzmi5dQ=";
    a0_13_2-1-honeycomb.arm = "sha256-df//YJxNSfYs+7uiyVNnuNL7cUqyXAosLcrMq3p6AjU=";
    a0_13_2-1.x86 = "sha256-lTKpsn7eDoQ0c7DIHTQJ88X/YrAC4C2Z9OndIlbigBQ=";
    a0_13_2-1.arm = "sha256-ZI+ikGPUBAAXE7CJ2UmcnZX1WITas5FqNiu47hneFq8=";
    a0_13_2-2-gingerbread.arm = "sha256-sVKKU9Ly+WXXekvxj3J1/j0gN53AwQQc5/9RTN3THiY=";
    a0_13_2-2-honeycomb.arm = "sha256-ir7hKyRaUBKHH2ni+eeyxwVK8Zda3Er94ki2OT8fzmg=";
    a0_13_2-2.x86 = "sha256-9OUAYxpzy43KGwPOacSHU7TAY9rgbBy45k8qeYuEb+I=";
    a0_13_2-2.arm = "sha256-ByKFoN1WOM0lxWpZK9ZcBNUnsqy6OPsNDtsv8mLVhCM=";
    a0_13_2-3-gingerbread.arm = "sha256-hkvC9geRT/7aA0P4abmTEkupueZPixZhb2bfhnKxWn8=";
    a0_13_2-3-honeycomb.arm = "sha256-xmhiYq4Rm/cidvE8MXqpOpa0KSOGcmQLdXJOQP8Je50=";
    a0_13_2-3.x86 = "sha256-oua6diafOpMPc6X3DHhzlsemnrvvXP4A9OREzttCjeU=";
    a0_13_2-3.arm = "sha256-sH9+hMzWzOZ8JoCK4Ai7TsM6NbJz/q281uSS14DiZHg=";
    a0_14_0-build1-honeycomb.arm = "sha256-xXszatwGt/wlgMGRDKwtI9JKnKyavO/NZePlVX04gBs=";
    a0_14_0-build1.arm = "sha256-BW6bkBnXXa3C6b4VEl3fClUESuL57mzU94uhMDmjbxI=";
    a0_14_0-build2-honeycomb.arm = "sha256-TMbXHoUGvdehdw7VkAtl1HH2JlH56axTBNAUyVI1lVg=";
    a0_14_0-build2.arm = "sha256-ebFrQ9Pz49/zJCebpH3TMr82SQpZohP2amJbAAuFflY=";
    a0_14_0-build3-gingerbread.arm = "sha256-1LffizFygm5PcS6iBkVs2AVWAd1Kcb2M/vpwvjHViKs=";
    a0_14_0-build3.arm = "sha256-a9VFUBQi2lUpqLpTsnHyphKj7PQwvtODmDzH8mwW3Fc=";
    a0_14_0-build4-gingerbread.arm = "sha256-/Pdeaz5JGznJNZ6TnXmKpUo6qZtOCo5ThJGO2F1LbJc=";
    a0_14_0-build4.arm = "sha256-DTxoaKPuiVKzKdw+EXn99cpkHU1JJpf7qmed1ubVA3c=";
    a0_14_0-build5.arm = "sha256-URXfhZieSHplFnGyufy9vNsnJtTNF3PYJVu6MzXasgs=";
    a0_14_0-build6.arm = "sha256-Uy3ZTnlaPPoOFm74wzS/g00TpQIz8vQww+Kw+lGNXLo=";
    a0_14_0-build7-honeycomb.arm = "sha256-SoQVlJJYa8H3fwjVBMH2QfbVaCMsFFuGHk2sUJc7UCk=";
    a0_14_0-build7.arm = "sha256-KB5bU3azPltHBaWTKPTNxx5/COhHgTbe69bFDq3ObNI=";
    a0_14_0.arm = "sha256-Op9hZg3pPlYEs3R1w41V2JkX2ev0guL+I8qtDe0bHDc=";
    a0_14_1.arm = "sha256-MLXgrnNiySOLBzfehBieiseYNWnT8z4aOEh5bQjww9s=";
    a0_14_2.arm = "sha256-GAoCIAmJI6gxVyTyVNUcQXbCqbPPJd5hyLg4zidV+5Q=";
    a0_14_3-1-gingerbread.arm = "sha256-WBZVCbppmYg1ONBODDiVVx2sAGsrxEUZ91YytrVmWdY=";
    a0_14_3-1-honeycomb.arm = "sha256-LvNQ5kyL1ZKlu+ojuTITbCEmf+o8AFxjTK0pZ3wzX+k=";
    a0_14_3-1.x86 = "sha256-qdSPkb+7QmlhAjcVwTJ8tmZM0wKV1vJN8BnbCrqfinU=";
    a0_14_3-1.arm = "sha256-GFAoIF98Xw/e7XnuOyaMT83B+Um5aUZzX5Zv1ZszAak=";
    a0_14_3-2-gingerbread.arm = "sha256-/sJI86+/MxJoP/fqBJpSZUsKuxwFVtUIeU73DF5kWN4=";
    a0_14_3-2-honeycomb.arm = "sha256-rViR25+KCL9VqPJu/qwab0bDPQFKMDZ9jIrie5WevyQ=";
    a0_14_3-2.x86 = "sha256-RdRw3Khjjn6icFlW4Z81Kab8wnoH9Iep2+hcky4u3ds=";
    a0_14_3-2.arm = "sha256-Z5kD7ReaSylOd3LUE/ziY4O4CybljsOiLpgpOZ/2sfc=";
    a0_15_0-build1-ics.arm = "sha256-ov/c7eFyhMMzdWhKetbuHvrXsHQXEpnFkzq8N268n2A=";
    a0_15_0-build1.arm = "sha256-CeoqyBB8B5v1ja03mGXOpIgQmJswCbmGXz/sx4zcIZw=";
    a0_15_0-build2-ics.arm = "sha256-CMrmN7mg81M/oWSwRHiAlxz/EgR30ElPDyZAGF+Rkss=";
    a0_15_0-build2.arm = "sha256-AdEfCMJVmjRUA+UarXtbcTIm14RjZXv7FFZxhzFpta8=";
    a0_15_0-build3.arm = "sha256-dnwSzkrYSa427YuSINk7sbzxaxzXTON/3OxZXvwi7iE=";
    a0_15_0-realms1.arm = "sha256-KuvjLutuO9b3EO4IvLHVFQRnLefNiyw5ilhKaR6mPWY=";
    a0_15_0-realms2.arm = "sha256-ZkQwV0VSQaER/6ytQUSJKFzC7Il4t9/jxPUZ/pu0RrA=";
    a0_15_0-realms4.arm = "sha256-8FDDFaCMMHTsk32Qcqmq1sdKjvSTVwvSqbDZ/pEBgUQ=";
    a0_15_0_1.x86 = "sha256-KoM8R1Wd4O82OKAk/x4url8/fisut1yCyZESx3Dfc2g=";
    a0_15_0_1.arm = "sha256-dR2qdlil9eO93JaYa2ox0nhUo+T8n8vEqOgCD7b38PA=";
    a0_15_0_50.arm = "sha256-gbK7haLylr2zdkqnaxcIAEuNXqGm5ehlm9iy1N1eMls=";
    a0_15_1_2.x86 = "sha256-ZzWqQjggPbDk+0zZZa2fjMI7QbqFPKy65mzDPp+1x7A=";
    a0_15_3_2.x86 = "sha256-LmeeDxwzZ7nKr/XJYs6LnjK6989SWY7oAfkdKvMXEmg=";
    a0_15_4.x86 = "sha256-xN4Uc6Tbap4mN3Ns9pDZxIsZaVoUQS1VKp5I8IYsL+E=";
    a0_15_6-ics.arm = "sha256-3kukP9mg6qAlehqaryFDSIVBdLsiizhmHUBailOba/0=";
    a0_15_6.x86 = "sha256-Wt7wTXKU3wtUr3AtmTr0qaHSHqCsesR9LmDBikmeqOU=";
    a0_15_6.arm = "sha256-eAnxKlMu+M0aN25pOEXZkTY5tS6ZJ8kMHOMdQBICaB4=";
    a0_15_90_2.arm = "sha256-/lyr9Z98NplLiQKKZHtH3lhPYi4cHYp28vfU1c6MK1w=";
    a0_15_90_8.arm = "sha256-FKn4UL2nZSVCqik1fwcK+oqrbauA8KtK6JSLjBW4fHk=";
    a0_16_2_2-FireTV.arm = "sha256-moCN2Uc7gah7W8zNf5XggN/pX8/kj45Sc0PVKdubbF0=";
    a0_16_2_2.x86 = "sha256-DJbPFAA5zRCoNl4U3HbNiOePMXQ1Q3ZZl7rhDqEnD28=";
    a0_17_0_1.arm = "sha256-FZCPo96VaqkE+N647Ksk4Tdy2friJKOVaZ2xqHHNdBQ=";
    a0_17_0_2.arm = "sha256-uECpFVwLDf+IBLfryLM7mePUR0ckvhscKEyE80aNIMk=";
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
        pname = "minecraftpe";
        inherit version;
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
