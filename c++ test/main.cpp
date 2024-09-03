#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

void runProgram(const std::string& programName) {
#ifdef _WIN32
    // Windows
    std::cout << "\t\t\t\tExecutando " << programName << "..." << std::endl;
    std::cout << "\t\t\t=================================================" << std::endl;

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::string command = programName + ".exe"; // Adiciona a extensão .exe para Windows

    if (CreateProcessA(NULL, const_cast<LPSTR>(command.data()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        if (exitCode != 0) {
            std::cerr << "Erro ao executar " << programName << ". Código de saída: " << exitCode << std::endl;
        } else {
            std::cout << "\n\t\t\t\t" << programName << " executado com sucesso!" << std::endl;
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Erro ao criar o processo para " << programName << ". Código de erro: " << GetLastError() << std::endl;
    }
#else
    // Linux
    std::cout << "\t\t\t\tExecutando " << programName << "..." << std::endl;
    std::cout << "\t\t\t=================================================" << std::endl;

    pid_t pid = fork();
    if (pid == 0) {
        // Processo filho
        execl(programName.c_str(), programName.c_str(), (char*)NULL);
        std::cerr << "Erro ao executar " << programName << std::endl;
        exit(1);
    } else if (pid > 0) {
        // Processo pai
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            std::cerr << "Erro ao executar " << programName << ". Código de saída: " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cout << "\n\t\t\t\t" << programName << " executado com sucesso!" << std::endl;
        }
    } else {
        std::cerr << "Erro ao criar o processo para " << programName << std::endl;
    }
#endif
}

int main() {
    std::cout << "\t\t\t===================PROGRAMA PRINCIPAL===================" << std::endl;
    std::cout << "\t\t\t\tIniciando a execucao dos programas..." << std::endl;
    
    runProgram("leitura_input");       // Nome do programa sem extensão
    runProgram("similaridade_jaccard"); // Nome do programa sem extensão
    runProgram("calculo_suporte_confianca"); // Nome do programa sem extensão

    std::cout << "\t\t\t=================================================" << std::endl;
    std::cout << "\t\t\t\tTodos os programas foram executados com sucesso!" << std::endl;
    std::cout << "\t\t\t=================================================" << std::endl;

    return 0;
}
