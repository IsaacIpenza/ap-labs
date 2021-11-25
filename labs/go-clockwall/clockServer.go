// Clock Server is a concurrent TCP server that periodically writes the time.
package main

import (
	"flag"
	"io"
	"log"
	"net"
	"os"
	"strconv"
	"time"
	"fmt"
)

func handleConn(c net.Conn, loc *time.Location) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, loc.String() + "\t : " + time.Now().In(loc).Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {

	port := flag.Int("port", 9090, "Port of the server")
	flag.Parse()

	timeZone := os.Getenv("TZ")
	location, err := time.LoadLocation(timeZone)
	if err != nil {
		log.Fatal(err)
	}

	listener, err := net.Listen("tcp", "localhost:"+strconv.Itoa(*port))
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("localhost:", *port, "-> time zone:", timeZone)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn, location) // handle connections concurrently
	}
}
