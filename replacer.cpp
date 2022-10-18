#include "replacer.h"

replacer::replacer(int template_id, QString output_file_path)
{
    QStringList arguments;
    arguments.append(qApp->applicationDirPath());
    arguments.append(QString("%1").arg(template_id));
    arguments.append(output_file_path);
    QProcess process;
    QString path_to_exe = qApp->applicationDirPath();
    path_to_exe.push_back("/replacer.exe");
    process.start(path_to_exe,arguments);
    process.waitForFinished();
}
