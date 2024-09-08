from json import dump, load
from subprocess import run

vcpkg_repo = "https://github.com/microsoft/vcpkg"
clib_vcpkg_registry_repo = "https://github.com/ThirdEyeSqueegee/CommonLibSSE-NG-vcpkg"
custom_vcpkg_registry_repo = "https://github.com/ThirdEyeSqueegee/vcpkg-ports"


def update_baselines():
    vcpkg_ref = (
        run(["git", "ls-remote", vcpkg_repo, "refs/heads/master"], capture_output=True)
        .stdout.decode()
        .splitlines()[0]
        .split()[0]
    )

    clib_vcpkg_registry_ref = (
        run(["git", "ls-remote", clib_vcpkg_registry_repo], capture_output=True)
        .stdout.decode()
        .splitlines()[0]
        .split()[0]
    )

    custom_vcpkg_registry_repo_ref = (
        run(["git", "ls-remote", custom_vcpkg_registry_repo], capture_output=True)
        .stdout.decode()
        .splitlines()[0]
        .split()[0]
    )

    with open("./vcpkg.json", "r") as f:
        vcpkg_json = load(f)

    vcpkg_json["builtin-baseline"] = vcpkg_ref
    vcpkg_json["vcpkg-configuration"]["registries"][0]["baseline"] = (
        clib_vcpkg_registry_ref
    )
    vcpkg_json["vcpkg-configuration"]["registries"][1]["baseline"] = (
        custom_vcpkg_registry_repo_ref
    )

    with open("./vcpkg.json", "w") as f:
        dump(vcpkg_json, f, indent=2)


if __name__ == "__main__":
    update_baselines()
