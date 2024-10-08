from os import listdir, path, mkdir
from shutil import copy as file_copy
from zipfile import ZIP_DEFLATED, ZipFile

def main():
    sources = glob_extension('src', '.c', exclude=['main.c', 'base.c'])
    headers = glob_extension('src', '.h')

    data = ['/* Single compilation unit for whole library */']
    sources.sort()
    for src in sources:
        with open(src, 'r') as f:
            data.append(f'/* File: {src} */')
            data.append(f.read())
    data = '\n'.join(data) + '\n'

    DIR = 'base'
    try:
        mkdir(DIR)
    except FileExistsError:
        pass

    with open(path.join(DIR, 'base.c'), 'w') as f:
        n = f.write(data)
        print(f'Wrote {n}B to base.c')

    for header in headers:
        file_copy(header, DIR)
    file_copy('LICENSE', DIR)

    with ZipFile('base.zip', 'w', compression=ZIP_DEFLATED, compresslevel=9) as zf:
        zf.mkdir(DIR)
        for header in listdir(DIR):
            zf.write(path.join(DIR, header))
    print(f'Created base.zip ({path.getsize("base.zip") // 1024}KiB)')


def glob_extension(dirpath: str, ext: str, exclude = None):
    res = []
    if exclude is None: exclude = []

    for entry in listdir(dirpath):
        entrypath =path.join(dirpath, entry)
        if path.isfile(entrypath) and entry.endswith(ext) and entry not in exclude:
            res.append(entrypath)
    return res

if __name__ == '__main__': main()
