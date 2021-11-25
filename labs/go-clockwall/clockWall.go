package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}

func getTime(p string, t chan io.Reader){
	conn, err := net.Dial("tcp", p)
	if err != nil {
		fmt.Print("A connection failed to " + p + "\n")

        log.Fatal(err)
    }
    t <- conn
}

func main() {
	
	if(len(os.Args) < 2){
		fmt.Println("Incorrect number of arguments")
	}

	args := os.Args[1:]
	data := make([]string, 0)

	for _, arg := range args {
		i := strings.Index(arg, "=") + 1
		data = append(data, arg[i:])
	}

	res := make(chan io.Reader)
	defer close(res)

	for {
		for _, port := range data {
			go getTime(port, res)
			time := <- res
			go mustCopy(os.Stdout, time)
		}
	}
}