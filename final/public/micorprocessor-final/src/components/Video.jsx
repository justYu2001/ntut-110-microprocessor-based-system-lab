const Video = () => {
    let videoSource = "";

    if (process.env.NODE_ENV === "development") {
        videoSource = "https://fakeimg.pl/1280x720/ffffff";
    } else {
        videoSource = "/api/camera";
    }

    return (
        <img src={videoSource} alt="camera" className="rounded-md"></img>
    )
}

export default Video;